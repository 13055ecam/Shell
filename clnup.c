#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include "clnup.h"

int clnup(char argv[25][50])
{
  char *directory = argv[1];
  DIR *dir;
  struct dirent *dp;
  char filename[255];
  char entireFilename[255];
  char s[1] = ".";
  char *token;
  char *type;

  if((dir=opendir(directory))==NULL){
    perror ("Can't open directory");
    return 1;
  }
  while((dp=readdir(dir))){
    strcpy(filename,dp->d_name);
    // This condition checks if the current entity is either a directory or a file.
    // If it is a directory no need to do any operations.
    if(fileOrFolder(directory,filename)==0){
      continue;
    }
    strcpy(entireFilename,filename);
    token = strtok(filename, s);
    while(token!=NULL){
      token=strtok(NULL,s);
      if(token!=NULL){type=token;}
    }
    if(type!=NULL){
      newDirectoryFile(type, directory, entireFilename);
    }
  }
  return 0;
}
char *newDirectoryFile(char *type, char *directory, char *filename){
  char *oldFilename;
  char *newFilename;
  type=typeVariable(type, directory);
  //Old directory
  oldFilename=concat(directory,"/");
  oldFilename=concat(oldFilename, filename);
  //New directory
  newFilename=concat(directory, "/");
  newFilename=concat(newFilename, type);
  newFilename=concat(newFilename, "/");
  newFilename=concat(newFilename, filename);
  // Move the file to the new location
  rename (oldFilename, newFilename);
  printf("%s\n",newFilename);
  return newFilename;
}
int fileOrFolder(char *directory, char *filename){
  char *testBuffer;
  testBuffer=concat(directory,"/");
  testBuffer=concat(testBuffer,filename);
  return chdir(testBuffer);
}
char *typeVariable(char *type, char *directory){
  char *buffer="Unknown";
  // Creates the adequat filename according to the extension.
  buffer = extension(type);
  // This condition enables the creation of a folder if the condition are met,
  // that is if buffer != "Unknown"
  // If we want to create an "Unknown" file we just have to remove the following if condition
  if(strncmp(buffer,"Unknown",10)!=0){
    printf("%s\n", "create folder");
    make_directory(directory, buffer);
  }
  return buffer;
}
char* concat( char *s1, char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
void make_directory(char *directory, char *buffer){
  directory=concat(directory, "/");
  directory=concat(directory, buffer);
  mkdir(directory,0700);
}
char *extension(char *type){
  char *buffer="Unknown";
  if(strncasecmp("pdf",type,10)==0){
    buffer = "Pdf files";
  }
  else if(strncasecmp("cmd",type,10)==0){
    buffer = "Command files";
  }
  else if(strncasecmp("jpg",type,10)==0 || strncasecmp("png",type,10)==0){
    buffer = "Image";
  }
  else if(strncasecmp("exe",type,10)==0){
    buffer = "Executable windows";
  }
  else if(strncasecmp("pptx",type,10)==0){
    buffer = "Powerpoint";
  }
  else if(strncasecmp("xlsx",type,10)==0){
    buffer = "Excel files";
  }
  else if(strncasecmp("ics",type,10)==0){
    buffer = "Timetable";
  }
  else if(strncasecmp("mp3",type,10)==0 || strncasecmp("wav",type,10)==0 || strncasecmp("flac",type,10)==0 || strncasecmp("aac",type,10)==0){
    buffer = "Audio files";
  }
  else if(strncasecmp("mkv",type,10)==0 || strncasecmp("mp4",type,10)==0){
    buffer = "Movies";
  }
  else if(strncasecmp("torrent",type,10)==0){
    buffer = "Torrent files";
  }
  else if(strncasecmp("zip",type,10)==0 || strncasecmp("gz",type,10)==0){
    buffer = "Zip files";
  }
  else if(strncasecmp("docx",type,10)==0){
    buffer = "Word files";
  }
  return buffer;
}

