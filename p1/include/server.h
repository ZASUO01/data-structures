#ifndef SERVER_H
#define SERVER_H

#include "mail.h"

typedef struct MailBox {
  int id;
  struct MailBox *left;
  struct MailBox *right;
  MailList *mail_list;
  int height;
} MailBox;

MailBox *create_account(MailBox *mb, int id);
void deliver_mail(MailBox *mb, int id, int priority, const char *message);
void read_mail(MailBox *mb, int id);
MailBox *delete_account(MailBox *mb, int id);
void delete_server(MailBox **mb);

#endif
