#include "InputManager.h"

void InputManager::HandleKeyPressed(int key)
{
    auto actionItr = mKeyToActionMap.find(key);
    if (actionItr != mKeyToActionMap.end())
    {
        if (actionItr->second->mPressedDelegate != nullptr)
        {
            actionItr->second->mPressedDelegate->Execute();
        }
    }
    
    auto axisItr = mKeyToAxisMap.find(key);
    if (axisItr != mKeyToAxisMap.end())
    {
        auto& axis = axisItr->second;
        
        if (key == axis->mPositiveKey)
        {
            axis->mValue += 1.0f;
        }
        else if (key == axis->mNegativeKey)
        {
            axis->mValue -= 1.0f;
        }
        
        if (axis->mDelegate != nullptr)
        {
            axis->mDelegate->Execute(axis->mValue);
        }
    }
}

void InputManager::HandleKeyReleased(int key)
{
    auto actionItr = mKeyToActionMap.find(key);
    if (actionItr != mKeyToActionMap.end())
    {
        if (actionItr->second->mReleasedDelegate != nullptr)
        {
            actionItr->second->mReleasedDelegate->Execute();
        }
    }
    
    auto axisItr = mKeyToAxisMap.find(key);
    if (axisItr != mKeyToAxisMap.end())
    {
        auto& axis = axisItr->second;
        
        if (key == axis->mPositiveKey)
        {
            axis->mValue -= 1.0f;
        }
        else if (key == axis->mNegativeKey)
        {
            axis->mValue += 1.0f;
        }
        
        if (axis->mDelegate != nullptr)
        {
            axis->mDelegate->Execute(axis->mValue);
        }
    }
}

void InputManager::AddActionMapping(const std::string& name, int key)
{
    ActionMappingPtr ptr = std::make_shared<ActionMapping>();
    ptr->mName = name;
    ptr->mKey = key;
    
    mNameToActionMap.emplace(name, ptr);
    mKeyToActionMap.emplace(key, ptr);
}

void InputManager::AddAxisMapping(const std::string& name, int positiveKey, int negativeKey)
{
    AxisMappingPtr ptr = std::make_shared<AxisMapping>();
    ptr->mName = name;
    ptr->mPositiveKey = positiveKey;
    ptr->mNegativeKey = negativeKey;
	ptr->mValue = 0.0f;
    
    mNameToAxisMap.emplace(name, ptr);
    mKeyToAxisMap.emplace(positiveKey, ptr);
    mKeyToAxisMap.emplace(negativeKey, ptr);
}

void InputManager::BindActionInternal(const std::string& name, InputEvent event, ActionDelegatePtr delegate)
{
    auto iter = mNameToActionMap.find(name);
    if (iter != mNameToActionMap.end())
    {
        if (event == InputEvent::IE_Pressed)
        {
            iter->second->mPressedDelegate = delegate;
        }
        else if (event == InputEvent::IE_Released)
        {
            iter->second->mReleasedDelegate = delegate;
        }
    }
}

void InputManager::BindAxisInternal(const std::string& name, AxisDelegatePtr delegate)
{
    auto iter = mNameToAxisMap.find(name);
    if (iter != mNameToAxisMap.end())
    {
        iter->second->mDelegate = delegate;
    }
}
