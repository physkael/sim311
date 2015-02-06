#include <string.h>
#include <stdio.h>
#include <TH1.h>
#include <iostream>

void readDE(const char* filename, TH1* h)
{
  FILE* f = fopen(filename, "r");

  if (f == NULL) {
    cerr << "Unable to open file " << filename << endl;
    return;
  }
  while (!feof(f)) {
    char s[100];
    char* tok;
    fgets(s, sizeof(s), f);
    if (strncmp("DE:", s, 3)) continue;
    tok = strtok(s+4, " ");
    double edep = strtod(tok, NULL);
    h->Fill(edep);
  }
  
  fclose(f);
}
