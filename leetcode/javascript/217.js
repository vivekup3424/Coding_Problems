/**
 * @param {number[]} nums
 * @return {boolean}
 */
var containsDuplicate = function (nums) {
  let obj = new Map();
  const n = nums.length;
  for (let i = 0; i < nums.length; i++) {
    if (obj.has(nums[i])) {
      obj.set(nums[i], obj.get(nums[i]) + 1);
    } else {
      obj.set(nums[i], 1);
    }
  }
  console.log(obj);
  //let's traverse the map and check if any element has
  //multiple occurence
  let result = false;
  obj.forEach((frequency, _) => {
    // console.log(`frequency = ${frequency}`);
    if (frequency > 1) {
      result = true;
    }
  });
  return result;
};

//let call the function
function main() {
  const nums = [1, 2, 3, 4];
  console.log(containsDuplicate(nums));
}

main();
