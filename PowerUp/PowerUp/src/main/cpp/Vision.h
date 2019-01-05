#ifndef SRC_VISION_H_
#define SRC_VISION_H_

extern volatile bool vtLookForLights;
extern volatile bool vtLookForBlue;
extern volatile bool vtFound;
extern volatile double vtOffsetX;
extern volatile double vtOffsetY;
extern volatile bool vtMostIsBlue;
extern void VisionThread();

#endif //SRC_VISION_H_
