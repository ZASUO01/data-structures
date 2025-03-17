#include "error-assert.h"
#include "parser.h"
#include "server.h"
#include "usage.h"
#include <string.h>

// string sizes
#define MAX_LINE 256
#define MAX_CMD 20

// aux function to remove possible line breaks in a string
void remove_line_beaks(char *line) {
  for (int i = 0; line[i] != '\0'; i++) {
    if (line[i] == '\n') {
      line[i] = '\0';
      break;
    }
  }
}

int main(int argc, char **argv) {
  // parse command line arguments
  Params params = parse_arguments(argc, argv);

  // open input file
  FILE *input_file = fopen(params.input_file_name, "r");
  error_assert((input_file != NULL), "Failed to open the input file");

  // process usage
  double init_time;
  if (params.use_proc_usage) {
    struct rusage init_usage = set_usage();
    init_time = get_proc_time(&init_usage);
  }

  // init mail server
  MailBox *server = NULL;

  // reading variables
  char line[MAX_LINE];
  char command[MAX_CMD];
  char tmp_msg[MAX_LINE];
  char *msg = NULL;
  int id, priority;

  // start of the output
  printf("START\n");

  // read file lines
  while (fgets(line, sizeof(line), input_file)) {
    // remove line breaks
    remove_line_beaks(line);

    // parse the line
    int read = sscanf(line, "%s %d", command, &id);
    error_assert((read == 2), "Invalid line");

    if (strcmp(command, "DELIVER") == 0) {
      read =
          sscanf(line, "%s %d %d %255[^\n]", command, &id, &priority, tmp_msg);
      error_assert((read == 4), "Invalid line");

      // allocate the read string
      msg = strdup(tmp_msg);
    }

    // execute the operation
    if (strcmp(command, "REGISTER") == 0) {
      server = create_account(server, id);
    } else if (strcmp(command, "DELIVER") == 0) {
      deliver_mail(server, id, priority, msg);

      // prevent memory leak
      free(msg);
      msg = NULL;
    } else if (strcmp(command, "QUERY") == 0) {
      read_mail(server, id);
    } else if (strcmp(command, "DELETE") == 0) {
      server = delete_account(server, id);
    }
  }

  // free the allocated string
  free(msg);

  // free server memory
  delete_server(&server);

  // end of the file
  printf("END\n");

  // close the input file
  int closed = fclose(input_file);
  error_assert((closed == 0), "Failed to close the input file");

  // process usage
  if (params.use_proc_usage) {
    struct rusage end_usage = set_usage();
    double end_time = get_proc_time(&end_usage);
    double total_time = end_time - init_time;

    printf("PROCESS USAGE IN SECONDS: %.5f\n", total_time);
  }

  return 0;
}
