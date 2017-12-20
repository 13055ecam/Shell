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
    buffer = "Word files"
  }
  return buffer;
}
