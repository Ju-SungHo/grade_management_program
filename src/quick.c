#include "quick.h"

/* ---------------------------------------------------------------------------------
 * function name : _median_search
 * arguments
 *  - pmember : struct pointer to reallocate
 *  - mode : sort order selected by user
 *  - left : start value's index in partition
 *  - right : end value's index in partition
 * return value
 *  - median : midium value's index in partition  
--------------------------------------------------------------------------------- */
__uint64 _median_search(STUDENT pmember[], unsigned char mode, __uint64 left, __uint64 right)
{
    __uint64 mid = (left+right)/2;
    __uint64 median = mid;
    
    if(mode == 1)
    {
        if(pmember[left].id > pmember[median].id)
            median = left;
        if(pmember[median].id > pmember[right].id)
            median = right;
        if(pmember[mid].id > pmember[median].id)
            median = left;
    }
    else if(mode == 2)
    {   
        if( mystrcmp(pmember[left].name,pmember[median].name) > 0 )
            median = left;
        if( mystrcmp(pmember[median].name,pmember[right].name) > 0 )
            median = right;
        if( mystrcmp(pmember[mid].name,pmember[median].name) > 0 )
            median = left;
    }
    else
    {
        if(pmember[left].average > pmember[median].average)
            median = left;
        if(pmember[median].average > pmember[right].average)
            median = right;
        if(pmember[mid].average > pmember[median].average)
            median = left;
    }

    return median;
    
}

/* ---------------------------------------------------------------------------------
 * function name : _partition
 * arguments
 *  - pmember : struct pointer to reallocate
 *  - mode : sort order selected by user
 *  - left : start index of partition
 *  - right : end index of partition
 * return value
 *  - high : pivot index in partiton
--------------------------------------------------------------------------------- */
__uint64 _partition(STUDENT pmember[], unsigned char mode, __uint64 left, __uint64 right)
{
    __uint64 low = left + 1;
    __uint64 high = right;
    __uint64 mid = _median_search(pmember,mode,left,right);

    STUDENT pivot = pmember[mid];
    swap(&pmember[left],&pmember[mid]);

    while(low <= high)
    {
        // 정렬 기준에 따른 code 분배
        switch(mode)
        {
            case 1:
                // left에서부터 pivot보다 큰 값을 찾아서 오른쪽으로 이동
                while(pivot.id >= pmember[low].id && low <= right)
                    low++;
                // right부터 pivot보다 작은 값을 찾아서 왼쪽으로 이동
                while(pivot.id <= pmember[high].id && high >= (left+1))
                    high--;
                break;

            case 2:
                // pivot이 크면 +, pivot이 작으면 -가 반환되기 때문에 
                while( (mystrcmp(pivot.name,pmember[low].name) > 0) && low <= right)
                    low++;

                while((mystrcmp(pivot.name,pmember[high].name) < 0)  && high >= (left+1))
                    high--;
                break;

            case 3:
                while(pivot.average >= pmember[low].average && low <= right)
                    low++;

                while(pivot.average <= pmember[high].average && high >= (left+1))
                    high--;
                break;
        }   
        // [작은 값, pivot, 큰 값]이 되도록 sort
        if(low <= high)
            swap(&pmember[low],&pmember[high]);
    }


    // pivot기준 최소 최대 partition 정렬이 끝났음으로 pivot과 high 변경
    swap(&pmember[left],&pmember[high]);
    return high;

}

/* ---------------------------------------------------------------------------------
 * function name : quick_sort
 * arguments
 *  - pmember : struct pointer for quick sort
 *  - mode : sort order selected by user
 *  - left : start index of partition
 *  - right : end index of partition
--------------------------------------------------------------------------------- */
void quick_sort(STUDENT pmember[], unsigned char mode, __uint64 left, __uint64 right, __uint64 size)
{
    __uint64 pivot;
    if(left <= right && right < size && left < size)
    {
        pivot =_partition(pmember, mode,left, right);
        quick_sort(pmember, mode, left, pivot-1, size);
        quick_sort(pmember, mode, pivot+1, right, size);
    }
}
