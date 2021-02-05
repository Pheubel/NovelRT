// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class InteropCatalogueTest : public testing::Test
{
public:
    NrtComponentCache componentCache = nullptr;
    NrtEntityCache entityCache = nullptr;
    NrtCatalogue catalogue = nullptr;

    NrtComponentTypeId intComponentTypeId = 0;
    NrtComponentTypeId sizeTComponentTypeId = 0;
    NrtComponentTypeId charComponentTypeId = 0;

    std::vector<EntityId> entityIdVector{};

protected:
    void SetUp() override
    {
        componentCache = Nrt_ComponentCache_Create(1);
        entityCache = Nrt_EntityCache_Create(1);
        catalogue = Nrt_Catalogue_Create(0, componentCache, entityCache);
        int32_t intDeleteState = -1;
        size_t sizeTDeleteState = -1;
        char charDeleteState = 'e';

        Nrt_ComponentCache_RegisterComponentTypeUnsafe(
            componentCache, sizeof(int32_t), &intDeleteState,
            [](auto lhs, auto rhs, auto) {
                auto intLhs =
                    reinterpret_cast<int32_t*>(Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(lhs));
                auto intRhs =
                    reinterpret_cast<int32_t*>(Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(rhs));
                *intLhs += *intRhs;
            },
            &intComponentTypeId);

        Nrt_ComponentCache_RegisterComponentTypeUnsafe(
            componentCache, sizeof(size_t), &sizeTDeleteState,
            [](auto lhs, auto rhs, auto) {
                auto sizeTLhs =
                    reinterpret_cast<size_t*>(Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(lhs));
                auto sizeTRhs =
                    reinterpret_cast<size_t*>(Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(rhs));
                *sizeTLhs += *sizeTRhs;
            },
            &sizeTComponentTypeId);

        Nrt_ComponentCache_RegisterComponentTypeUnsafe(
            componentCache, sizeof(char), &charDeleteState, [](auto, auto, auto) {}, &charComponentTypeId);


        auto compViewInt = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, intComponentTypeId);
        auto compViewSizeT = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, sizeTComponentTypeId);
        auto compViewChar = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, charComponentTypeId);

        int32_t intInput = 10;
        size_t sizeTInput = 100;
        char charInput = 'a';

        Nrt_UnsafeComponentView_PushComponentUpdateInstruction(compViewInt, 0, &intInput);
        Nrt_UnsafeComponentView_PushComponentUpdateInstruction(compViewSizeT, 0, &sizeTInput);
        Nrt_UnsafeComponentView_PushComponentUpdateInstruction(compViewChar, 0, &charInput);

        Nrt_ComponentCache_PrepAllBuffersForNextFrame(componentCache,
                                                      reinterpret_cast<NrtEntityIdVector>(&entityIdVector));
    }

    void TearDown() override
    {
        Nrt_ComponentCache_Destroy(componentCache);
        Nrt_EntityCache_Destroy(entityCache);
        Nrt_Catalogue_Destroy(catalogue);
    }
};

TEST_F(InteropCatalogueTest, CanGetValidComponentView)
{
    auto compView = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, charComponentTypeId);
    NrtSparseSetMemoryContainer_ConstIterator beginIterator = nullptr;
    NrtSparseSetMemoryContainer_ConstIterator endIterator = Nrt_UnsafeComponentView_end(compView);

    for (beginIterator = Nrt_UnsafeComponentView_begin(compView);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(beginIterator, endIterator) == NRT_TRUE;
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(beginIterator))
    {
        size_t outputId = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorView itView = nullptr;
        ASSERT_EQ(Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(beginIterator, &outputId, &itView),
                  NRT_SUCCESS);

        char result = 'z';
        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation(itView, &result);

        EXPECT_EQ(result, 'a');

        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(itView);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(beginIterator);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(endIterator);
}

TEST_F(InteropCatalogueTest, CanRemoveComponentFromEntityBasedOnView)
{
    auto compView = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, intComponentTypeId);
    NrtSparseSetMemoryContainer_ConstIterator beginIterator = nullptr;
    NrtSparseSetMemoryContainer_ConstIterator endIterator = Nrt_UnsafeComponentView_end(compView);

    for (beginIterator = Nrt_UnsafeComponentView_begin(compView);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(beginIterator, endIterator) == NRT_TRUE;
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(beginIterator))
    {
        size_t outputId = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorView itView = nullptr;
        ASSERT_EQ(Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(beginIterator, &outputId, &itView),
                  NRT_SUCCESS);

        ASSERT_EQ(Nrt_UnsafeComponentView_RemoveComponent(compView, outputId), NRT_SUCCESS);
        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(itView);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(beginIterator);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(endIterator);
    Nrt_ComponentCache_PrepAllBuffersForNextFrame(componentCache, reinterpret_cast<NrtEntityIdVector>(&entityIdVector));

    NrtComponentBufferMemoryContainer ptr = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(componentCache, intComponentTypeId, &ptr), NRT_SUCCESS);
    EXPECT_EQ(Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(ptr), 0);
}

