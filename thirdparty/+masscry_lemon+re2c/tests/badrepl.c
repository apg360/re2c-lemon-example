#include <badcode.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE *input;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  switch (argc)
  {
  case 1:
    input = stdin;
    break;
  case 2:
    input = fopen(argv[1], "r");
    if (input == NULL) 
    {
      perror("fopen");
      return EXIT_FAILURE;
    }
    break;
  default:
    fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
    return EXIT_FAILURE;
  }

  BC_CORE core = NULL;
  bcStatus_t status = bcCoreNew(&core);
  if (status != BC_OK)
  {
    fprintf(stderr, "bcCoreNew failed: %d\n", status);
    return EXIT_FAILURE;
  }
  
  if (input == stdin)
  {
    fprintf(stdout, "%s", "? ");
    fflush(stdout);
  }

  while ((nread = getline(&line, &len, input)) != -1) 
  {
    status = bcCoreExecute(core, line, NULL);
    switch (status)
    {
    case BC_OK:
      break;
    case BC_PARSE_NOT_FINISHED:
      fprintf(stdout, "%s", "~ ");
      fflush(stdout);
      continue;
    case BC_EMPTY_EXPR:
      fprintf(stdout, "%s", "? ");
      fflush(stdout);
      continue;
    default:
      fprintf(stderr, "! %s (%d)\n", bcStatusString(status), status);
      fprintf(stdout, "%s", "? ");
      fflush(stdout);
      continue;
    }

    BC_VALUE result = NULL;
    if (bcCoreResult(core, &result) == BC_OK)
    {
      if (result != NULL)
      {
        fprintf(stdout, "= ");
        bcValuePrint(stdout, result);
        fprintf(stdout, "\n");
      }
    }

    fprintf(stdout, "%s", "? ");
    fflush(stdout);
  }

  bcCoreDelete(core);

  free(line);
  if (input != stdin)
  {
    fclose(input);
  }
  return EXIT_SUCCESS;
}
