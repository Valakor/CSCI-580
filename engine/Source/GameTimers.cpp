#include "GameTimers.h"

GameTimerManager::GameTimerManager()
	:mNextTimerId(0)
	,mAreTimersTicking(false)
{

}

void GameTimerManager::Tick(float deltaTime)
{
    mAreTimersTicking = true;
    
    for (auto& iter : mActiveTimers)
    {
        auto& timer = iter.second;
        
        if (timer.mStatus == TimerStatus::Active)
        {
            timer.mRemainingTime -= deltaTime;
            
            if (timer.mRemainingTime <= 0.0f)
            {
                if (timer.mDelegate != nullptr)
                {
                    timer.mDelegate->Execute();
                }
                
                if (timer.mIsLooping)
                {
                    timer.mRemainingTime = timer.mDuration;
                }
                else
                {
                    timer.mStatus = TimerStatus::Cleared;
                    mClearedTimers.push_back(iter.first);
                }
            }
        }
    }
    
    for (auto& iter : mClearedTimers)
    {
        auto timer = mActiveTimers.find(iter);
        RemoveFromObjMap(timer->second.mObj, timer->first);
		mActiveTimers.erase( timer );
    }
    mClearedTimers.clear();
    
    for (auto& iter : mPendingTimers)
    {
        iter.second.mStatus = TimerStatus::Active;
        mActiveTimers.emplace(iter.first, iter.second);
    }
    mPendingTimers.clear();
    
    mAreTimersTicking = false;
}

void GameTimerManager::ClearTimer(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		// We can just remove this from pending timers
		RemoveFromObjMap(iter->second.mObj, handle);
		mPendingTimers.erase(iter);
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mStatus = Cleared;
			mClearedTimers.push_back(handle);
		}
	}
}

void GameTimerManager::PauseTimer(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		iter->second.mStatus = Paused;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mStatus = Paused;
		}
	}
}

void GameTimerManager::UnpauseTimer(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		iter->second.mStatus = Pending;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mStatus = Active;
		}
	}
}

float GameTimerManager::GetRemainingTime(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		return iter->second.mRemainingTime;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			return iter->second.mRemainingTime;
		}
	}

	// Unknown timer
	return -1.0f;
}

void GameTimerManager::AddTime(const TimerHandle& handle, float time)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		iter->second.mRemainingTime += time;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mRemainingTime += time;
		}
	}
}

void GameTimerManager::ClearAllTimers(Object* obj)
{
	auto iter = mObjToHandlesMap.find(obj);
	if (iter != mObjToHandlesMap.end())
	{
		for (auto& t : iter->second)
		{
			ClearTimer(t);
		}

		mObjToHandlesMap.erase(iter);
	}
}

void GameTimerManager::SetTimerInternal(TimerHandle& outHandle, Object* obj, TimerDelegatePtr delegate, float duration, bool looping)
{
    outHandle.mValue = mNextTimerId++;
    
    TimerInfo newTimer;
    newTimer.mObj = obj;
    newTimer.mDelegate = delegate;
    newTimer.mDuration = duration;
    newTimer.mRemainingTime = duration;
    newTimer.mIsLooping = looping;
    newTimer.mHandle = outHandle;
    
    if (mAreTimersTicking)
    {
        newTimer.mStatus = TimerStatus::Pending;
        mPendingTimers.emplace(outHandle, newTimer);
    }
    else
    {
        newTimer.mStatus = TimerStatus::Active;
        mActiveTimers.emplace(outHandle, newTimer);
    }
    
    AddToObjMap(obj, outHandle);
}

void GameTimerManager::AddToObjMap(Object* obj, const TimerHandle& handle)
{
	auto iter = mObjToHandlesMap.find(obj);
	// Do we already know of this object?
	if (iter != mObjToHandlesMap.end())
	{
		iter->second.emplace(handle);
	}
	else
	{
		std::unordered_set<TimerHandle> temp;
		temp.emplace(handle);
		mObjToHandlesMap.emplace(obj, temp);
	}
}

void GameTimerManager::RemoveFromObjMap(Object* obj, const TimerHandle& handle)
{
	auto iter = mObjToHandlesMap.find(obj);
	if (iter != mObjToHandlesMap.end())
	{
		auto handleIter = iter->second.find(handle);
		if (handleIter != iter->second.end())
		{
			iter->second.erase(handleIter);
		}
	}
}
