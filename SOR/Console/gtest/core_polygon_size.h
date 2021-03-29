#ifndef CORE_POLYGON_SIZE_H_INCLUDED
#define CORE_POLYGON_SIZE_H_INCLUDED

TEST(core_polygon_size,1)
{
    CORE::Polygon a;
    pair<int,int> x={2,3};
    a.add(x);
    ASSERT_TRUE(a.size()==1);
}

#endif // CORE_POLYGON_SIZE_H_INCLUDED
