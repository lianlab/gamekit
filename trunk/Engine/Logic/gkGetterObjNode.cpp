/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Nestor Silveira.

    Contributor(s): none yet.
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
#include "OgreRoot.h"
#include "gkWindowSystem.h"
#include "gkGetterObjNode.h"
#include "gkEngine.h"
#include "gkScene.h"
#include "gkLogger.h"
#include "gkUtils.h"
#include "gkRigidBody.h"
#include "gkGameObject.h"
#include "btBulletDynamicsCommon.h"

gkGetterObjNode::gkGetterObjNode(gkLogicTree *parent, size_t id)
: gkLogicNode(parent, id), m_type(OBJ_NAME), m_obj(0), m_position(gkVector3::ZERO),
m_rotation(gkQuaternion::IDENTITY)
{
	ADD_ISOCK(UPDATE_OBJ, false);
	ADD_ISOCK(UPDATE_STATE, true);
	ADD_ISOCK(NAME, "");
	ADD_OSOCK(OBJ, 0);
	ADD_ISOCK(X, 0);
	ADD_ISOCK(Y, 0);
	ADD_ISOCK(RESET, false);
	ADD_OSOCK(HAS_OBJ, false);
	ADD_OSOCK(HIT_POINT, gkVector3::ZERO);
	ADD_OSOCK(POSITION, gkVector3::ZERO);
	ADD_OSOCK(ROTATION, gkQuaternion::IDENTITY);
}

bool gkGetterObjNode::evaluate(gkScalar tick)
{
	if(GET_SOCKET_VALUE(UPDATE_OBJ))
	{
		m_obj = 0;

		if(!GET_SOCKET_VALUE(RESET))
		{
			if(m_type == OBJ_NAME)
			{
				gkScene* pScene = gkEngine::getSingleton().getActiveScene();

				m_obj = pScene->getObject(GET_SOCKET_VALUE(NAME));
			}
			else
			{
				GK_ASSERT(m_type == SCREEN_XY && "Invalid type");

				Ogre::Ray ray = gkUtils::CreateCameraRay(GET_SOCKET_VALUE(X), GET_SOCKET_VALUE(Y));

				gkVector3 rayPoint;

				btCollisionObject* pCol = gkUtils::PickBody(ray, rayPoint);

				if(pCol)
				{
					SET_SOCKET_VALUE(HIT_POINT, rayPoint);
			
					m_obj = static_cast<gkObject*>(pCol->getUserPointer())->getObject();
				}
			}
		}

		SET_SOCKET_VALUE(HAS_OBJ, m_obj ? true : false);
		SET_SOCKET_VALUE(OBJ, m_obj);

		updateState();

	}
	else if(GET_SOCKET_VALUE(UPDATE_STATE))
	{
		updateState();
	}

	return false;
}

void gkGetterObjNode::updateState()
{
	gkVector3 position(gkVector3::ZERO);
	gkQuaternion rotation(gkQuaternion::IDENTITY);

	if(m_obj)
	{
		position = m_obj->getPosition();
		rotation = m_obj->getOrientation();
	}

	if(m_position != position)
	{
		m_position = position;
		SET_SOCKET_VALUE(POSITION, m_position);
	}

	if(m_rotation != rotation)
	{
		m_rotation = rotation;
		SET_SOCKET_VALUE(ROTATION, m_rotation);
	}

}
