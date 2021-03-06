// @(#)root/gl:$Id$
// Author:  Matevz Tadel, Feb 2007

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include "TGLLockable.h"
#include <TError.h>

//______________________________________________________________________
// TGLLockable
//
// Simple locking interface used by viewer and scene.


ClassImp(TGLLockable);

TGLLockable::TGLLockable() :
   fLock      (kUnlocked)
{
   // Constructor
}

//______________________________________________________________________________
Bool_t TGLLockable::TakeLock(ELock lock) const
{
   // Lock the object in mode 'lock'. Return TRUE if successful, FALSE
   // if the object is already locked.

   if (LockValid(lock) && fLock == kUnlocked) {
      fLock = lock;
      if (gDebug>3) {
         Info("TGLLockable::TakeLock", "'%s' took %s",
              LockIdStr(), LockName(fLock));
      }
      return kTRUE;
   }
   Error("TGLLockable::TakeLock", "'%s' unable to take %s, already %s",
         LockIdStr(), LockName(lock), LockName(fLock));
   return kFALSE;
}

//______________________________________________________________________________
Bool_t TGLLockable::ReleaseLock(ELock lock) const
{
   // Release current lock, make sure it the same as the 'lock' argument.
   // Returns TRUE on success, FALSE on failure.

   if (LockValid(lock) && fLock == lock) {
      fLock = kUnlocked;
      if (gDebug>3) {
         Info("TGLLockable::ReleaseLock", "'%s' released %s",
              LockIdStr(), LockName(lock));
      }
      return kTRUE;
   }
   Error("TGLLockable::ReleaseLock", "'%s' unable to release %s, is %s",
         LockIdStr(), LockName(lock), LockName(fLock));
   return kFALSE;
}

//______________________________________________________________________________
const char* TGLLockable::LockName(ELock lock)
{
   // Return name-string for given lock-type.

   static const char* names[] =
      { "Unlocked", "DrawLock", "SelectLock", "ModifyLock" };

   if (lock <= kModifyLock) {
      return names[lock];
   } else {
      return "<unknown-lock>";
   }
}

//______________________________________________________________________________
Bool_t TGLLockable::LockValid(ELock lock)
{
   // Test if lock is a valid type to take/release.
   // kUnlocked is never valid in these cases.

   switch(lock) {
      case kDrawLock:
      case kSelectLock:
      case kModifyLock:
         return kTRUE;
      default:
         return kFALSE;
   }
}
