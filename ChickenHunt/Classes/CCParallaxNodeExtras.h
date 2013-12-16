
//
//  CCParallaxNodeExtras.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/12/13.
//
//

#ifndef __ChickenHunt__CCParallaxNodeExtras__
#define __ChickenHunt__CCParallaxNodeExtras__

#include "cocos2d.h"

USING_NS_CC;

class CCParallaxNodeExtras : public CCParallaxNode {
    
    public :
    
    // Need to provide a constructor
    CCParallaxNodeExtras();
    
    // just to avoid ugly later cast and also for safety
    static CCParallaxNodeExtras * node();
    
    // Facility method (it’s expected to have it soon in COCOS2DX)
    void incrementOffset(CCPoint offset, CCNode* node);
} ;



#endif /* defined(__ChickenHunt__CCParallaxNodeExtras__) */
