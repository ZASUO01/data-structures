#include "server.h"
#include "error-assert.h"
#include "mail.h"
#include <stdlib.h>

#define MAX(a, b) (a > b ? a : b)

// aux function return the current height of a node
static int height(MailBox *mb) { return (mb != NULL) ? mb->height : 0; }

// update the height of the current node based on child subtrees
static void update_height(MailBox **mb) {
  if (*mb != NULL) {
    (*mb)->height = 1 + MAX(height((*mb)->left), height((*mb)->right));
  }
}

// get the difference betwee child subtrees height
static int balance_factor(MailBox *mb) {
  if (mb != NULL) {
    return (height(mb->left) - height(mb->right));
  }

  return 0;
}

// single right rotation
static MailBox *rotate_right(MailBox *x) {
  MailBox *y = x->left;
  MailBox *yr = y->right;

  y->right = x;
  x->left = yr;

  update_height(&x);
  update_height(&y);

  return y;
}

// single left rotation
static MailBox *rotate_left(MailBox *y) {
  MailBox *x = y->right;
  MailBox *xl = x->left;

  x->left = y;
  y->right = xl;

  update_height(&y);
  update_height(&x);

  return x;
}

// perform rotations to balance the current subtree if needed
MailBox *balance(MailBox *mb) {
  update_height(&mb);
  int balance = balance_factor(mb);

  // case left left
  if (balance > 1 && balance_factor(mb->left) >= 0) {
    return rotate_right(mb);
  }

  // case right right
  if (balance < -1 && balance_factor(mb->right) <= 0) {
    return rotate_left(mb);
  }

  // case left right
  if (balance > 1 && balance_factor(mb->left) < 0) {
    mb->left = rotate_left(mb->left);
    return rotate_right(mb);
  }

  // case right left
  if (balance < -1 && balance_factor(mb->right) > 0) {
    mb->right = rotate_right(mb->right);
    return rotate_left(mb);
  }

  // no rotation needed
  return mb;
}

// allocate and init a new MailBox
static MailBox *create_mail_box(int id) {
  // allocate the required memory
  MailBox *mb = (MailBox *)malloc(sizeof(MailBox));
  error_assert((mb != NULL), "Failed to allocate memory");

  // init values
  mb->id = id;
  mb->height = 1;
  mb->left = NULL;
  mb->right = NULL;

  mb->mail_list = create_mail_list();

  return mb;
}

// free the target MailBox memory
static void delete_mail_box(MailBox **mb) {
  if (mb != NULL && *mb != NULL) {
    delete_mail_list(&(*mb)->mail_list);

    free(*mb);
    *mb = NULL;
  }
}

// returns the min left node of the current subtree
static MailBox *min_mail_box(MailBox *mb) {
  MailBox *current = mb;
  while (current != NULL && current->left != NULL) {
    current = current->left;
  }

  return current;
}

// inserts a new account to the server
MailBox *create_account(MailBox *mb, int id) {
  // create the account if not created yet
  if (mb == NULL) {
    printf("OK: ACCOUNT %d REGISTERED\n", id);
    return create_mail_box(id);
  }

  if (id < mb->id) {
    // go to the left
    mb->left = create_account(mb->left, id);
  } else if (id > mb->id) {
    // go to the right
    mb->right = create_account(mb->right, id);
  } else {
    // account already created
    printf("ERROR: ACCOUNT %d ALREADY EXISTS\n", id);
    return mb;
  }

  // balance the current subtree
  return balance(mb);
}

// add a new mail to the target account
void deliver_mail(MailBox *mb, int id, int priority, const char *message) {
  // account not found
  if (mb == NULL) {
    printf("ERROR: ACCOUNT %d DOESN'T EXIST\n", id);
    return;
  }

  if (id < mb->id) {
    // go to the left
    return deliver_mail(mb->left, id, priority, message);
  } else if (id > mb->id) {
    // go to the right
    return deliver_mail(mb->right, id, priority, message);
  } else {
    // account found
    insert_mail(mb->mail_list, priority, message);

    printf("OK: MESSAGE TO ACCOUNT %d DELIVERED\n", id);
    return;
  }
}

// display the first mail of the list if it's not empty
void read_mail(MailBox *mb, int id) {
  // account not found
  if (mb == NULL) {
    printf("ERROR: ACCOUNT %d DOESN'T EXIST\n", id);
    return;
  }

  if (id < mb->id) {
    // go to the left
    return read_mail(mb->left, id);
  } else if (id > mb->id) {
    // go to the right
    return read_mail(mb->right, id);
  } else {
    // account found

    if (mb->mail_list->list_size > 0) {
      char *message = get_first_mail(mb->mail_list);
      printf("MESSAGE: %s\n", message);

      free(message);
      message = NULL;
    } else {
      printf("EMPTY MAIL BOX\n");
    }

    return;
  }
}

// delete an account with all associated data
MailBox *delete_account(MailBox *mb, int id) {
  // account not found
  if (mb == NULL) {
    printf("ERROR: ACCOUNT %d DOESN'T EXIST\n", id);
    return NULL;
  }

  if (id < mb->id) {
    // go to the left
    mb->left = delete_account(mb->left, id);
  } else if (id > mb->id) {
    // go to the right
    mb->right = delete_account(mb->right, id);
  } else {
    // account found
    printf("OK: ACCOUNT %d DELETED\n", id);
    MailBox *tmp;

    // case 1 - no child or one child
    if (mb->left == NULL) {
      tmp = mb->right;
      delete_mail_box(&mb);
      return tmp;
    } else if (mb->right == NULL) {
      tmp = mb->left;
      delete_mail_box(&mb);
      return tmp;
    }
    // case 2 - both child exists
    else {
      // get min node of the right subtree
      tmp = min_mail_box(mb->right);

      // free the current MailBox list
      delete_mail_list(&mb->mail_list);

      // copy data from the tmp MailBox
      mb->id = tmp->id;
      mb->mail_list = copy_mail_list(tmp->mail_list);

      // delete the copied MailList
      mb->right = delete_account(mb->right, tmp->id);
    }
  }

  return balance(mb);
}

// free all memory allocated for the server
void delete_server(MailBox **mb) {
  if (mb != NULL && *mb != NULL) {
    delete_server(&(*mb)->left);
    delete_server(&(*mb)->right);

    delete_mail_list(&(*mb)->mail_list);

    free(*mb);
    *mb = NULL;
  }
}
