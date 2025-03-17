#ifndef MAIL_H
#define MAIL_H

typedef struct {
  int priority;
  int order;
  char *message;
} Mail;

typedef struct {
  Mail **list;
  int list_size;
  int elements_order;
} MailList;

MailList *create_mail_list();
void insert_mail(MailList *ml, int priority, const char *message);
MailList *copy_mail_list(MailList *ml);
char *get_first_mail(MailList *ml);

void delete_mail_list(MailList **ml);

#endif
