#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

//We want every single .cpp file to be able to access these variables, so we use extern (Try this w/o Extern!)
extern SDL_Window* theWindow;
extern SDL_Renderer* theRenderer;

//One of the few times you wont supply a const with a value up front
extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int LINE_W;

//Lets also declare our functions
bool InitSDL();
void Close();
void Play();

#endif // GLOBALS_H_INCLUDED
