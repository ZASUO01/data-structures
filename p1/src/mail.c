#include "mail.h"
#include "error-assert.h"
#include <stdlib.h>
#include <string.h>

// allocate and init a new Mail
static Mail *create_mail(int priority, int order, const char *message) {
  // allocate memory
  Mail *mail = (Mail *)malloc(sizeof(Mail));
  error_assert((mail != NULL), "Failed to allocate memory");

  // init variables
  mail->priority = priority;
  mail->order = order;
  mail->message = strdup(message);

  return mail;
}

// free the memory allocated for a single Mail
static void delete_mail(Mail **mail) {
  if (mail != NULL && *mail != NULL) {
    free((*mail)->message);
    (*mail)->message = NULL;

    free(*mail);
    *mail = NULL;
  }
}

// build the reap from a parent i
static void heapfy(MailList *ml, int i, int n) {
  // first child
  int j = (i * 2) + 1;

  // current parent
  Mail *x = ml->list[i];

  // if j is inside the list yet
  while (j <= n) {
    // case there's other child
    if (j < n) {
      if (ml->list[j]->priority < ml->list[j + 1]->priority) {
        j++;
      } else if (ml->list[j]->priority == ml->list[j + 1]->priority) {
        if (ml->list[j]->order > ml->list[j + 1]->order) {
          j++;
        }
      }
    }

    // if parent priority is greater than current child
    if (x->priority > ml->list[j]->priority) {
      break;
    }

    // if the priorities are the same the lower order should come first
    if (x->priority == ml->list[j]->priority) {
      if (x->order < ml->list[j]->order) {
        break;
      }
    }

    // swap elements
    ml->list[i] = ml->list[j];
    i = j;
    j = (i * 2) + 1;
  }

  ml->list[i] = x;
}

// build the heap for all parents in the list
static void build_heap(MailList *ml, int n) {
  for (int i = (n / 2) - 1; i >= 0; i--) {
    heapfy(ml, i, n - 1);
  }
}

// allocate and init a new MailList
MailList *create_mail_list() {
  // allocate the required memory
  MailList *ml = (MailList *)malloc(sizeof(MailList));
  error_assert((ml != NULL), "Failed to allocate memory");

  // init values
  ml->elements_order = 0;
  ml->list_size = 0;

  // allocate the list
  ml->list = (Mail **)malloc(sizeof(Mail *));
  error_assert((ml->list != NULL), "Failed to allocate memory");

  return ml;
}

// create and add a new Mail to the MailList
void insert_mail(MailList *ml, int priority, const char *message) {
  Mail *mail = create_mail(priority, ++ml->elements_order, message);

  Mail **tmp = (Mail **)realloc(ml->list, (ml->list_size + 1) * sizeof(Mail *));
  error_assert((tmp != NULL), "Failed to allocate memory");

  ml->list = tmp;
  ml->list[ml->list_size++] = mail;

  build_heap(ml, ml->list_size);
}

// get the first element of the list and remove it
char *get_first_mail(MailList *ml) {
  char *first = strdup(ml->list[0]->message);
  Mail *tmp = ml->list[0];

  ml->list[0] = ml->list[ml->list_size - 1];
  ml->list_size--;

  delete_mail(&tmp);

  build_heap(ml, ml->list_size);

  return first;
}

// create a new MailList and copy all data from a source
MailList *copy_mail_list(MailList *ml) {
  MailList *copy = (MailList *)malloc(sizeof(MailList));
  error_assert((copy != NULL), "Failed to allocate memory");

  copy->list_size = ml->list_size;
  copy->elements_order = ml->elements_order;

  copy->list = (Mail **)malloc(ml->list_size * sizeof(Mail *));
  error_assert((copy->list != NULL), "Failed to allocate memory");

  for (int i = 0; i < ml->list_size; i++) {
    copy->list[i] = create_mail(ml->list[i]->priority, ml->list[i]->order,
                                ml->list[i]->message);
  }

  return copy;
}

// free all the memory allocated for the target MailList
void delete_mail_list(MailList **ml) {
  if (ml != NULL && *ml != NULL) {
    for (int i = 0; i < (*ml)->list_size; i++) {
      delete_mail(&(*ml)->list[i]);
    }

    free((*ml)->list);
    (*ml)->list = NULL;

    free(*ml);
    *ml = NULL;
  }
}
