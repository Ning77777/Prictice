#include <iostream>
#include <utility>
#include <vector>

using namespace std;

pair<int, pair<int, int> > CrossMediaSubarray(pair<int, int> domain, int median, vector<int>& nums);
pair<int, pair<int, int> > FindMaximumSubarray(pair<int, int> domain, vector<int>& nums);

int main()
{
    vector<int> nums = {-1, -2, -3, -10, -4, -7, -2, -5};
    auto result = FindMaximumSubarray({0, 7}, nums);
    cout<<result.first<<endl;
    cout<<result.second.first<<"----"<<result.second.second<<endl;
    return 0;
}

pair<int, pair<int, int> > FindMaximumSubarray(pair<int, int> domain, vector<int>& nums) {
    if(domain.first > domain.second) 
        return {0, {-1, -1}};
    if(domain.first == domain.second) {
        if(nums[domain.first] >= 0)
            return {nums[domain.first], domain};
        else 
            return {0, {-1, -1}};
    }
    int medium = (domain.first+domain.second)/2;
    auto leftArray = FindMaximumSubarray({domain.first, medium-1}, nums);
    auto mediumArray = CrossMediaSubarray(domain, medium, nums);
    auto rightArray = FindMaximumSubarray({medium+1, domain.second}, nums);
    if(leftArray.first >= mediumArray.first && leftArray.first >= rightArray.first) 
        return leftArray;
    else if(mediumArray.first >= leftArray.first  && mediumArray.first >= rightArray.first)
        return mediumArray;
    else if(rightArray.first >= leftArray.first && rightArray.first >= mediumArray.first)
        return rightArray;
}

pair<int, pair<int, int> > CrossMediaSubarray(pair<int, int> domain, int median, vector<int>& nums) {
    int sum=0, lhsMaximum=0, rhsMaximum=0, lhs(-1), rhs(-1);
    for(int i = median; i >= domain.first; --i) {
        sum = sum + nums[i];
        if(sum > lhsMaximum) {
            lhsMaximum = sum;
            lhs = i;
        }
    }
    if(lhs == -1) 
        return {0, {-1, -1}};
    sum=0;
    for(int i = median+1; i <= domain.second; ++i) {
        sum = sum + nums[i];
        if(sum > rhsMaximum) {
            rhsMaximum = sum;
            rhs = i;
        }
    }
    if(rhs == -1) 
        return {lhsMaximum, {lhs, median}};
    else 
        return {lhsMaximum+rhsMaximum, {lhs, rhs}};
}