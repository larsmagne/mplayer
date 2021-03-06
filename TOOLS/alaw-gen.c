/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <stdlib.h>

// sox -t raw -A -r 8000 -b alaw.alaw -t sw alaw.out

int main(void){
int i;
FILE *f;

f=fopen("alaw.dat","wb");
for(i=0;i<256;i++) fwrite(&i,1,1,f);
fclose(f);

system("sox -t raw -A -r 8000 -b alaw.dat -t sw alaw.out");

printf("// Generated by TOOLS/alaw-gen.c\n\n");

printf("#ifndef MPLAYER_ALAW_H\n");
printf("#define MPLAYER_ALAW_H\n");

printf("\nconst short alaw2short[]={\n");

f=fopen("alaw.out","rb");
for(i=0;i<256;i++){
  signed short x;
  fread(&x,2,1,f);
  printf("%7d",x);
  if(i!=255) putchar(',');
  if((i&7)==7) printf("\n");
}
fclose(f);
printf("};\n");

system("sox -t raw -U -r 8000 -b alaw.dat -t sw alaw.out");

printf("\nconst short ulaw2short[]={\n");

f=fopen("alaw.out","rb");
for(i=0;i<256;i++){
  signed short x;
  fread(&x,2,1,f);
  printf("%7d",x);
  if(i!=255) putchar(',');
  if((i&7)==7) printf("\n");
}
fclose(f);
printf("};\n\n");

printf("#endif /* MPLAYER_ALAW_H */\n");

return 0;
}
