#!/bin/bash
#By Domenico Luciani aka DLion
# http://blog.dlion.tk
# http://about.me/DLion
say() 
{ 
  mplayer -really-quiet -ao alsa "http://translate.google.com/translate_tts?tl=it&q=$*" 
}

say $*

