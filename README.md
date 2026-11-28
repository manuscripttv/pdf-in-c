# pdf-in-c

## Lets create a PDF file in C

### (1) hello.pdf

#### notes

- pdf readers start at the end of the document
- build the trailer
- build the header
- file hierarchy:   > (obj 1) catalog 
                    > (obj 2) page tree 
                    > (obj 3) page 
                    > (obj 4) font 
                    > (obj 5) content stream 

#### general structure

```text
%PDF-1.4
1 0 obj Catalog
2 0 obj Pages
3 0 obj Page
4 0 obj Font
5 0 obj Stream
xref
0 N+1                
0000000000 65535 f  // <- 1st entry. starts at byte 0. hence n+1
0000000xxx xxxxx n
0000000xxx xxxxx n
0000000xxx xxxxx n
0000000xxx xxxxx n
0000000xxx xxxxx n

trailer
<< /Size N+1 /Root 1 0 R >>
startxref
byte_offset_of_xref_start
%%EOF
```
