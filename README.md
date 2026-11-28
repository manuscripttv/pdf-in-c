# pdf-in-c

## lets create a pdf file in c

### general notes

PDF specifications: [PDF 32000-1:2008 Spec](https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf)

- pdf readers start at the end of the document
- build the trailer
- build the header
- build body objects
- update xref table

#### object hierarchy: 

```text
- (obj 1) catalog 
- (obj 2) page tree 
- (obj 3) page 
- (obj 4) font 
- (obj 5) content stream 
```

### (1) hello.pdf

#### general structure

```text
%PDF-1.4                        <--- file header
1 0 obj Catalog                 <--- file body objects (see hierarchy above)
2 0 obj Pages
3 0 obj Page
4 0 obj Font
5 0 obj Stream
xref                            <--- cross reference table
0 N+1                
0000000000 65535 f              <--- 1st entry. starts at byte 0. hence n+1.
0000000xxx xxxxx n
0000000xxx xxxxx n
0000000xxx xxxxx n
0000000xxx xxxxx n
0000000xxx xxxxx n

trailer                         <--- trailer
<< /Size N+1 /Root 1 0 R >>
startxref
byte_offset_of_xref_start
%%EOF
```
