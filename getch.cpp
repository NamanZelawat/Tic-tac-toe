/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  newt = old; //make new settings same as old settings
  newt.c_lflag &= ~ICANON; //disable buffered i/o
  newt.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &newt); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
 
/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
/* 
Read 1 character without echo 
getch() function definition.
*/
char getch(void) 
{
  return getch_(0);
}