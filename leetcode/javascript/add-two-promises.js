/**
 * @param {Promise} promise1
 * @param {Promise} promise2
 * @return {Promise}
 */
var addTwoPromises = async function(promise1, promise2){
    const values = await Promise.all([promise1,promise2]);
    return values[0]+values[1];
};