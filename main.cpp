// The Main HAM Library
#include <mygba.h>

// The HEL Library
#include <hel2.h>

// Various includes
#include "header.h"

// Function: main() ======================================================================
int main()
{
  // Variables
  map_fragment_info_ptr bg_background;

  // Initialize HAMlib
  ham_Init();

  // Set system prefetch
  //hel_SysSetPrefetch(TRUE);
 
  // Initialize Splash-Screen System
  hel_SplashInit((void*)g_SplashScreenSystemBuffer);

  // Enter bg mode 4 for the splash screen
  ham_SetBgMode(4);

  // Splashscreen 1
  hel_Splash
    (
       (u16*)ResData(RES_SPLASHSCREEN_RAW),  // pBitmap
       (u16*)ResData(RES_SPLASHSCREEN_PAL),  // pPalette
       RGB(0,0,0),                  // InBlendColor
       RGB(0,0,0),                  // OutBlendColor
       60,                          // BlendDelay
       2000,                        // DisplayDelay
       500,                         // ContinueDelay
       COMPRESSION_TYPE_NONE,       // CompressionType,
       0                            // Flags
    );
  
  // Quit the splashscreen
  hel_SplashQuit();

  // Setup the background mode
  ham_SetBgMode(1);

  // Initialize the text display system
  ham_InitText(0);

  // Initialize the palettes
  ham_LoadBGPal((void*)background_Palette, 256);
  ham_LoadObjPal((void*)object_Palette, 256);

  // Set the Text Color
  ham_SetTextCol(195, 40);
 
  // Setup the tileset for our image
  ham_bg[1].ti = ham_InitTileSet((void*)background_Tiles, SIZEOF_16BIT(background_Tiles), 1, 1);

  // Setup the map for our image
  ham_bg[1].mi = ham_InitMapEmptySet(3,0);
  bg_background = ham_InitMapFragment((void*)background_Map, 60, 20, 0, 0, 60, 20, 0);

  // Copy (the whole) map to BG0 at x=0, y=0
  ham_InsertMapFragment(bg_background, 1, 0, 0);

  // Display the background
  ham_InitBg(1, 1, 2, 1);

  // Setup the array spot
  array_spot = (32768 * dir_dk) + (4096 * animcnt);

  // setup the initial state of the frame bits counter
  frameCounter = 0;

  // Setup the dk
  dk = ham_CreateObj(
       (void *)&dk_Bitmap[array_spot],
       0,3,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,dk_x,dk_y);

  // Start the VBL interrupt handler
  ham_StartIntHandler(INT_TYPE_VBL, (void*)&vbl_func);

  while (1)
  {
    if (newframe)
    {
      // Write some stuff to the screen
      ham_DrawText(1, 1, "480x160 background");
      ham_DrawText(1, 2, "Arrows to scroll left-right");

      ham_DrawText(1, 17, "scroll-x: %5d", map_x);
      ham_DrawText(1, 18, "frame: %5d", frameCounter);

      // Let the user move the map around
      if (F_CTRLINPUT_RIGHT_PRESSED)
      {
        if (map_x < (480 - 240))
          ham_SetBgXY(1, ++map_x, 0);
      }
      if (F_CTRLINPUT_LEFT_PRESSED)
      {
        if (map_x > 0)
          ham_SetBgXY(1, --map_x, 0);
      }
      newframe = 0; // No longer a new frame
    } // End of if(newframe)
  } // End of while(1)

  return 0;
} // End of main()

//********************** =================================================================
// Function: vbl_func()
// Purpose: VBL function
//**********************
// VBL function
void vbl_func()
{
  // update background
  newframe = 1;

  // Copy dk sprite to hardware
  ham_CopyObjToOAM();

  // Process the following every VBL
  query_buttons(); // Query for user input
  update_dk_gfx(); // Apply dk's new graphic
  update_dk_pos(); // Apply dk's new position

  ++frames; // Increment the frame counter
  frameCounter += 4096; // increment frame bits counter

	return;
} // End of vbl_func()

//****************************** =========================================================
// Function: query_buttons()
// Purpose: Query for user input
//******************************
void query_buttons()
{
  // RIGHT only
  if (F_CTRLINPUT_RIGHT_PRESSED)
  {
    if (dk_x < 176)
      ++dk_x;
    dir_dk = ANIM_RIGHT;
    return;
  }

  // LEFT only
  if (F_CTRLINPUT_LEFT_PRESSED)
  {
    if (dk_x > 0)
      --dk_x;
    dir_dk = ANIM_LEFT;
    return;
  }

  return;
} // End of query_buttons()


//*********************************** ====================================================
// Function: update_dk_gfx()
// Purpose: Apply dk's new graphic
//***********************************
void update_dk_gfx()
{
  // We'll only update the animation every 7th frame
  if (frames > 9) {
    // Reset the frame counter
    frames = 0;

    // reset the frame bits counter
    frameCounter = 0;

    // Figure out where to load the image from
    array_spot = (32768 * dir_dk) + (4096 * animcnt);

    // Update it
    ham_UpdateObjGfx(dk, (void*)&dk_Bitmap[array_spot]);

    // Increment the animation counter
    if (animcnt == 7)
        animcnt = 0;
    else
      animcnt++;
  }

  return;
} // End of update_dk_gfx()

//************************************ ===================================================
// Function: update_dk_pos()
// Purpose: Apply dk's new position
//************************************
void update_dk_pos()
{
  ham_SetObjX(dk, dk_x);
  ham_SetObjY(dk, dk_y);

  return;
} // End of update_dk_pos()

