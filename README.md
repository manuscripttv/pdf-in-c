# pdf-in-c

## Lets create PDF file in C

### hello.pdf

- pdf readers start at the end of the document
- lets open a file and write as we create the pdf 
- we built the trailer
- now lets build the header
- lets add the first entry in the xref table
- file structure: 
    - obj 1             > obj 2     > obj 3 > obj 4 > obj 5
    - document catalog  > page tree > page  > font  > content stream

- general structure of this pdf file

xref
0 N+1                
0000000000 65535 f                  // <- 1st entry. starts at byte 0. hence n+1

trailer
<< /Size N /Root 1 0 R >>
startxref
byte_offset_of_xref_start
%%EOF

