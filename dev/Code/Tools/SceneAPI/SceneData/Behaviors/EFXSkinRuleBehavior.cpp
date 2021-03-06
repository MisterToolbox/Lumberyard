/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#ifdef MOTIONCANVAS_GEM_ENABLED

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/std/smart_ptr/make_shared.h>
#include <SceneAPI/SceneCore/Containers/Scene.h>
#include <SceneAPI/SceneCore/Containers/SceneGraph.h>
#include <SceneAPI/SceneCore/Containers/Utilities/Filters.h>
#include <SceneAPI/SceneCore/DataTypes/Groups/IActorGroup.h>
#include <SceneAPI/SceneCore/DataTypes/GraphData/IMaterialData.h>
#include <SceneAPI/SceneData/Rules/EFXSkinRule.h>
#include <SceneAPI/SceneData/Behaviors/EFXSkinRuleBehavior.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace SceneData
        {
            AZ_CLASS_ALLOCATOR_IMPL(EFXSkinRuleBehavior, SystemAllocator, 0)

            EFXSkinRuleBehavior::EFXSkinRuleBehavior()
            {
                BusConnect();
            }

            EFXSkinRuleBehavior::~EFXSkinRuleBehavior()
            {
                BusDisconnect();
            }

            void EFXSkinRuleBehavior::InitializeObject(const Containers::Scene& scene, DataTypes::IManifestObject& target)
            {
                if (target.RTTI_IsTypeOf(DataTypes::IActorGroup::TYPEINFO_Uuid()))
                {
                    DataTypes::IActorGroup* actorGroup = azrtti_cast<DataTypes::IActorGroup*>(&target);

                    // EFX-TODO: Check if the sceneGraph contain skin data.
                    Containers::RuleContainer& rules = actorGroup->GetRuleContainer();
                    if (!rules.ContainsRuleOfType<DataTypes::IEFXSkinRule>())
                    {
                        rules.AddRule(AZStd::make_shared<SceneData::EFXSkinRule>());
                    }
                }
            }
        } // SceneData
    } // SceneAPI
} // AZ
#endif //MOTIONCANVAS_GEM_ENABLED