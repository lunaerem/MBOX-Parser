#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define VERSION "0.0.1"

int read_mbox(const char *filename) {
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    fprintf(stderr, "Error: Could not open mbox archive \"%s\"\n", filename);
    return 1;
  }

  char line[1024];
  int msg_count = 0;

  while (fgets(line, sizeof(line), fp)) {
    // Check if the line starts with "From "
    if (strncmp(line, "From ", 5) == 0) {
      msg_count++;
      printf("Found message %s\n", line);
      // Process message headers and body until the next "From "
    } else if (strncmp(line, "To: ", 4) == 0) {
      printf("%s\n", line);
    } else if (strncmp(line, "From: ", 6) == 0) {
      printf("%s\n", line);
    } else if (strncmp(line, "Subject: ", 9) == 0) {
      printf("%s\n\n", line);
    }
  }

  printf("Total Messages Found: %d\n", msg_count);

  fclose(fp);

  return 0;
}

int write_html(const char *file) {
  FILE *htmlFile = fopen(file, "w");

  if (htmlFile == NULL) {
    fprintf(stderr, "Error: Could not create file.\n");
    return 1;
  }

  fprintf(htmlFile, "<!DOCTYPE html>\n");
  fprintf(htmlFile,
          "<html>\n<head>\n<title>Test Generated Page</title>\n</head>\n");
  fprintf(htmlFile, "<body>\n");
  fprintf(htmlFile, "<h1>Header 1</h1>\n");
  fprintf(htmlFile,
          "<p>This file was created programmatically as a test.</p>\n");
  fprintf(htmlFile, "</body>\n</html>");

  fclose(htmlFile);

  printf("HTML file 'index.html' created successfully.\n");
  return 0;
}
/*
#define START_HTML(f) fprintf(f, "<html>")
#define END_HTML(f) fprintf(f, "</html>")
#define H1(f, text) fprintf(f, "<h1>%s</h1>", text)

int main() {
    FILE *f = fopen("output.html", "w");
    START_HTML(f);
    H1(f, "Header 1");
    END_HTML(f);
    fclose(f);
    return 0;
}
*/
int main(int argc, char *argv[]) {

  int opt;
  int rv = 0;

  // Checking through the arguments
  while ((opt = getopt(argc, argv, "vht:m:")) != -1) {
    switch (opt) {
    case 'v':
      printf("mbox-parser version: %s\n", VERSION);
      return rv;
    case 'h':
      fprintf(stderr, "Help is currently not implemented yet, sorry.\n");
      return rv;
    case 't':
      return read_mbox("Test.mbox");
    case 'm':
      return write_html(optarg);
    case '?':
      break;
    }
  }

  return rv;
}
