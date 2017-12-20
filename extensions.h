char *extension(char *type){
  char *buffer="Unknown";
  if(strncmp("pdf",type,10)==0){
    buffer = "Pdf files";
  }
  else if(strncmp("cmd",type,10)==0){
    buffer = "Command files";
  }
  else if(strncmp("jpg",type,10)==0 || strncmp("png",type,10)==0){
    buffer = "Image";
  }
  else if(strncmp("exe",type,10)==0){
    buffer = "Executable windows";
  }
  else if(strncmp("pptx",type,10)==0){
    buffer = "Powerpoint";
  }
  else if(strncmp("xlsx",type,10)==0){
    buffer = "Excel files";
  }
  else if(strncmp("ics",type,10)==0){
    buffer = "Timetable";
  }
  else if(strncmp("mp3",type,10)==0 || strncmp("wav",type,10)==0 || strncmp("flac",type,10)==0 || strncmp("aac",type,10)==0){
    buffer = "Audio files";
  }
  else if(strncmp("mkv",type,10)==0 || strncmp("mp4",type,10)==0){
    buffer = "Movies";
  }
  else if(strncmp("torrent",type,10)==0){
    buffer = "Torrent files";
  }
  else if(strncmp("zip",type,10)==0 || strncmp("gz",type,10)==0){
    buffer = "Zip files";
  }
  else if(strncmp("docx",type,10)==0){
    buffer = "Word files"
  }
  return buffer;
}
