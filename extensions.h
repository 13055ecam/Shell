char *extension(char *type){
  char *buffer="Unknown";
  if(strncmp("pdf",type,10)==0){
    buffer = "pdf files";
  }
  else if(strncmp("cmd",type,10)==0){
    buffer = "cmd files";
  }
  else if(strncmp("jpg",type,10)==0 || strncmp("png",type,10)==0){
    buffer = "image";
  }
  else if(strncmp("exe",type,10)==0){
    buffer = "executable windows";
  }
  else if(strncmp("pptx",type,10)==0){
    buffer = "powerpoint";
  }
  else if(strncmp("xlsx",type,10)==0){
    buffer = "excel";
  }
  else if(strncmp("ics",type,10)==0){
    buffer = "timetable";
  }
  else if(strncmp("mp3",type,10)==0 || strncmp("wav",type,10)==0 || strncmp("flac",type,10)==0 || strncmp("aac",type,10)==0){
    buffer = "audio files";
  }
  else if(strncmp("mkv",type,10)==0 || strncmp("mp4",type,10)==0){
    buffer = "movies";
  }
  else if(strncmp("torrent",type,10)==0){
    buffer = "torrent files";
  }
  else if(strncmp("zip",type,10)==0 || strncmp("gz",type,10)==0){
    buffer = "zip files";
  }
  return buffer;
}
