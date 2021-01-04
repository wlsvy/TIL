using System;
using System.Linq;
using System.Collections.Generic;

public class Solution
{
    long answer = 0;
    long totalPerson;

    long GetSumAndUpdateAns(long time, List<long> list)
    {
        long sum = list.Aggregate((long)0, (l, r) => l + time / r);
        if (sum >= totalPerson)
        {
            answer = Math.Min(answer, time);
        }
        return sum;
    }

    public long solution(int n, int[] times)
    {
        var ts = new List<long>(times.Select((i) => (long)i));
        ts.Sort();
        totalPerson = n;
        answer = ts.Last() * (long)n;
        long low = 0, high = times.Last() * (long)n, mid;

        while (high - low > 1)
        {
            mid = (high + low) / 2;
            if (GetSumAndUpdateAns(mid, ts) >= totalPerson)
            {
                high = mid;
            }
            else
            {
                low = mid;
            }
        }
        for (long i = -1; i <= 1; i++)
        {
            GetSumAndUpdateAns(low + i, ts);
        }
        return answer;
    }
}
