#ifndef DEFS_HPP
#define DEFS_HPP

#define SCREEN_HEIGHT           600
#define SCREEN_WIDTH            800

#define SIM_WIDTH_IN_METERS     20.0f
#define SIM_HEIGHT_IN_METERS    (SCREEN_HEIGHT / SIM_SCALE) 
#define SIM_SCALE               (SCREEN_WIDTH / SIM_WIDTH_IN_METERS)
#define SIM_WIDTH               (SCREEN_WIDTH / SIM_SCALE)
#define SIM_HEIGHT              (SCREEN_HEIGHT / SIM_SCALE)

#define FPS_TARGET              60


#endif  // DEFS_HPP