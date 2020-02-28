#include "orders.h"

#include <stdlib.h>

int Orders_init(Orders *orders, int number_of_floors)
{
    orders->up_orders = malloc(sizeof(int) * number_of_floors);
    orders->down_orders = malloc(sizeof(int) * number_of_floors);

    if (!orders->up_orders || !orders->down_orders)
    {
        return -1;
    }

    for (int i = 0; i < number_of_floors; i++)
    {
        orders->up_orders[i] = 0;
        orders->down_orders[i] = 0;
    }

    orders->floor_count = number_of_floors;

    return 0;
}

void Orders_free(Orders *orders)
{
    free(orders->up_orders);
    free(orders->down_orders);
}

int Orders_floor_is_in(Orders *orders, OrderType type, int floor)
{
    if (type == UP && orders->up_orders[floor])
    {
        return 1;
    }
    else if (type == DOWN && orders->down_orders[floor])
    {
        return 1;
    }
    else if (type == BOTH && (orders->down_orders[floor] || orders->up_orders[floor]))
    {
        return 1;
    }
    return 0;  
}

int Orders_extreme_value_of(Orders *orders, OrderType type)
{
    if (type == UP)
    {
        for (int i = 0; i < orders->floor_count; i++)
        {
            if (orders->up_orders[i] == 1)
            {
                return i;
            }
        }
        return -1;
    }
    else if (type == DOWN)
    {
        for (int i = orders->floor_count - 1; i >= 0; i--)
        {
            if (orders->down_orders[i] == 1)
            {
                return i;
            }
        }
        return -1;
    }
    return -1;
}

void Orders_remove(Orders *orders, OrderType type, int floor)
{
    if (type == UP)
    {
        orders->up_orders[floor] = 0;
    }
    else if (type == DOWN)
    {
        orders->down_orders[floor] = 0;
    }
    else if (type == BOTH)
    {
        orders->up_orders[floor] = 0;
        orders->down_orders[floor] = 0;
    } 
}

int Orders_order_over(Orders *orders, OrderType type, int floor)
{
    for (int i = floor + 1; i < orders->floor_count; i++)
    {
        if (type == UP && orders->up_orders[i] == 1)
        {
            return 1;
        }
        else if (type == DOWN && orders->down_orders[i] == 1)
        {
            return 1;
        }
        else if (type == BOTH && (orders->up_orders[i] == 1 || orders->down_orders[i] == 1))
        {
            return 1;
        }
    }
    return 0;
}

int Orders_order_under(Orders *orders, OrderType type, int floor)
{
    for (int i = 0; i < floor; i++)
    {
        if (type == UP && orders->up_orders[i] == 1)
        {
            return 1;
        }
        else if (type == DOWN && orders->down_orders[i] == 1)
        {
            return 1;
        }
        else if (type == BOTH && (orders->up_orders[i] == 1 || orders->down_orders[i] == 1))
        {
            return 1;
        }
    }
    return 0;   
}


void Orders_remove_all(Orders *orders)
{
    for (int i = 0; i < orders->floor_count; i++)
    {
        orders->up_orders[i] = 0;
        orders->down_orders[i] = 0;
    }
}
