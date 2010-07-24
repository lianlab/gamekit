/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): xat
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkStats_h_
#define _gkStats_h_

#include "OgreSingleton.h"
#include "OgreTimer.h"

class gkStats : public Ogre::Singleton<gkStats>
{

private:
    Ogre::Timer* m_clock;
    
    unsigned long m_render;
    unsigned long m_logicBricks;
    unsigned long m_logicNodes;
    unsigned long m_physics;
    unsigned long m_dbvt;
    unsigned long m_sound;
    unsigned long m_bufswaplod;

public:
    gkStats();

    void resetClock(void);

    void startClock(void);

    void stopRenderClock(void);
    void stopLogicBricksClock(void);
    void stopLogicNodesClock(void);
    void stopPhysicsClock(void);
    void stopDbvtClock(void);
    void stopSoundClock(void);
    void stopBufSwapLodClock(void);

    unsigned long getRenderMicroSeconds(void) {return m_render; }
    unsigned long getLogicBricksMicroSeconds(void) {return m_logicBricks; }
    unsigned long getLogicNodesMicroSeconds(void)  {return m_logicNodes;}
    unsigned long getPhysicsMicroSeconds(void)     {return m_physics;}
    unsigned long getDbvtMicroSeconds(void)        {return m_dbvt;}
    unsigned long getSoundMicroSeconds(void)       {return m_sound;}
    unsigned long getBufSwapLodMicroSeconds(void)       {return m_bufswaplod;}

    static gkStats& getSingleton(void);
    static gkStats* getSingletonPtr(void);
};

#endif //_gkStats_h_