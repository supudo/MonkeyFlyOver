// Defines =====================================================================
#define ANIM_RIGHT 1
#define ANIM_LEFT 0

// Global Variables ============================================================
// background
u8 newframe = 1; // Signifies a new frame
u16 map_x = 0; // X position of the map
// sprite
u32 dir_dk = 0; // Direction the dk is facing
u8 dk; // Sprite index for the dk
u32 dk_x = 110; // X position of the dk
u32 dk_y =  50; // Y position of the dk
u32 animcnt = 0; // Current frame of animation
u32 frames = 0; // Global frame counter
u32 array_spot = 0; // Sprite's current image location
u32 frameCounter = 0; // frame bit counter

// Workmemory for Splash-Screen System =========================================
u8 ATTR_EWRAM ATTR_ALIGNED(4) g_SplashScreenSystemBuffer[HEL_SUBSYSTEM_SPLASH_REQUIREDMEMORY];
