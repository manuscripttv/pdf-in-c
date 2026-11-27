#include <stdio.h>
#include <string.h>

long write_object(FILE *pdf, int n, const char *body) {
  long start = ftell(pdf);
  fprintf(pdf, "%d 0 obj\n", n);
  fprintf(pdf, "%s\n", body);
  fprintf(pdf, "endobj\n");
  return start;
}

long write_stream(FILE *pdf, int n, const char *data) {
  long start = ftell(pdf);
  fprintf(pdf, "%d 0 obj\n", n);
  fprintf(pdf, "<< /Length %d >>\n", (int)strlen(data));
  fprintf(pdf, "stream\n");
  fprintf(pdf, "%s\n", data);
  fprintf(pdf, "endstream\n");
  fprintf(pdf, "endobj\n");
  return start;
}

int main() {

  int tot_entries_xreftab = 5;                // TODO: set before compiling
  long offset[tot_entries_xreftab + 1];       // write byte offset
  int pages = 1;                              // TODO
  const char *content = "BT "                 // begin text
                        "/F1 24 Tf "          // font F1 at 24 points
                        "72 770 Td "          // move to x,y
                        "(Hello, World!) Tj " // text
                        "ET";                 // end text

  FILE *f;

  f = fopen("op/hello.pdf", "wb");
  if (!f) {
    printf("error creating file!\n");
    return 1;
  }

  // file header
  fprintf(f, "%%PDF-1.4\n");

  // file body
  // object 1: document catalog
  offset[1] = write_object(f, 1, "<< /Type /Catalog /Pages 2 0 R >>");

  // object 2: page tree
  char buf[64];
  snprintf(buf, sizeof(buf), "<< /Type /Pages /Kids [3 0 R] /Count %d>>",
           pages);
  offset[2] = write_object(f, 2, buf);

  // object 3: page
  char bufpage[256];
  snprintf(bufpage, sizeof(bufpage),
           "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Resources << "
           "/Font << /F1 4 0 R >> >> /Contents 5 0 R >>");
  offset[3] = write_object(f, 3, bufpage);

  // object 4: font
  offset[4] = write_object(
      f, 4, "<< /Type /Font /Subtype /Type1 /BaseFont /Courier >>");

  // object 5: content!
  offset[5] = write_stream(f, 5, content);

  // cross reference table
  long xref_start = ftell(f);
  fprintf(f, "xref\n");
  fprintf(f, "0 %d\n", tot_entries_xreftab + 1);
  fprintf(f, "0000000000 65535 f \n"); // 20 bytes exactly incl \n
  for (int n = 1; n <= tot_entries_xreftab; n++) {
    fprintf(f, "%010ld 00000 n \n", offset[n]);
  }

  // trailer
  //
  fprintf(f, "trailer\n");
  fprintf(f, "<< /Size %d /Root 1 0 R >>\n", tot_entries_xreftab + 1);

  fprintf(f, "startxref\n");
  fprintf(f, "%ld\n", xref_start); // byte offset.
  fprintf(f, "%%%%EOF\n");

  fclose(f);
  return 0;
}
