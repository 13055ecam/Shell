#ifndef CLNUP_H
#define CLNUP_H
void stats();
  char *strtok(char *, const char *);
  void clnup(char *);
  char *newDirectoryFile(char *, char *, char *);
  int fileOrFolder(char *, char *);
  char *typeVariable(char *type, char *directory);
  char* concat( char *s1, char *s2);
  void make_directory(char *, char *);
#endif /* CLNUP_H */
