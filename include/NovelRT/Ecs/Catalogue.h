// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_CATALOGUE_H
#define NOVELRT_ECS_CATALOGUE_H

#include "ComponentCache.h"
#include "EcsUtils.h"
#include "SystemScheduler.h"
#include "SparseSet.h"
#include "EntityCache.h"

namespace NovelRT::Ecs
{
    template <typename TComponent>
    class ComponentView
    {
        private:
        size_t _poolId;
        ComponentBuffer<TComponent>& _componentBuffer;
        
        public:
        ComponentView(size_t poolId, ComponentBuffer<TComponent>& targetBuffer) noexcept : _poolId(poolId), _componentBuffer(targetBuffer) {}

        void PushComponentUpdateInstruction(EntityId entity, TComponent instructionState) noexcept
        {
            _componentBuffer.PushComponentUpdateInstruction(_poolId, entity, instructionState);
        }

        void AddComponent(EntityId entity, TComponent initialValue = TComponent{}) noexcept
        {
            PushComponentUpdateInstruction(entity, initialValue);
        }

        void RemoveComponent(EntityId entity) noexcept
        {
            PushComponentUpdateInstruction(entity, _componentBuffer.GetDeleteInstructionState());
        }

        bool TryAddComponent(EntityId entity, TComponent initialValue = TComponent{}) noexcept
        {
            if (_componentBuffer.HasComponent(entity))
            {
                return false;
            }

            AddComponent(entity, initialValue);
            return true;
        }

        bool TryRemoveComponent(EntityId entity)
        {
            if (!_componentBuffer.HasComponent(entity))
            {
                return false;
            }

            RemoveComponent(entity);
            return true;
        }

        [[nodiscard]] TComponent GetComponent(EntityId entity) const
        {
            return _componentBuffer.GetComponent(entity);
        }

        [[nodiscard]] size_t GetImmutableDataLength() const noexcept
        {
            return _componentBuffer.GetImmutableDataLength();
        }

        // clang-format off
        [[nodiscard]] auto begin() const noexcept
        {
            return _componentBuffer.begin();
        }

        [[nodiscard]] auto end() const noexcept
        {
            return _componentBuffer.end();
        }
        // clang-format on
    };

    class Catalogue
    {
        private:
        size_t _poolId;
        ComponentCache& _componentCache;
        EntityCache& _entityCache;
        std::vector<EntityId> _createdEntitiesThisFrame;

        public:
        Catalogue(size_t poolId, ComponentCache& componentCache, EntityCache& entityCache) noexcept : _poolId(poolId), _componentCache(componentCache), _entityCache(entityCache), _createdEntitiesThisFrame(std::vector<EntityId>{})
        {

        }

        template<typename TComponent>
        [[nodiscard]] auto GetComponentView()
        {
            return ComponentView<TComponent>(_poolId, _componentCache.GetComponentBuffer<TComponent>());
        }

        template<typename... TComponents>
        [[nodiscard]] auto GetComponentViews()
        {
            return std::make_tuple(ComponentView<TComponents>(_poolId, _componentCache.GetComponentBuffer<TComponents>())...);
        }

        [[nodiscard]] EntityId CreateEntity() noexcept
        {
            EntityId returnId = Atom::getNextEntityId();
            _createdEntitiesThisFrame.push_back(returnId);
            return returnId;
        }

        void DeleteEntity(EntityId entity) noexcept
        {
            if (std::find(_createdEntitiesThisFrame.begin(), _createdEntitiesThisFrame.end(), entity) != _createdEntitiesThisFrame.end())
            {
                return;
            }
            
            _entityCache.RemoveEntity(_poolId, entity);
        }
    };
}

#endif //!NOVELRT_ECS_CATALOGUE_H