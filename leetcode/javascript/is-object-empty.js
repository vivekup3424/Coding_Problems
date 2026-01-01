/**
 * @param {Object | Array} obj
 * @return {boolean}
 */
var isEmpty = function (obj) {
    if (JSON.stringify(obj).length <= 2) return true;
    return false;
}

/**
 * @param {Object | Array} obj
 * @return {boolean}
 */
var isEmpty2 = function (obj) {
    return Object.keys(obj).length == 0;
}

/**
 * @param {Object | Array} obj
 * @return {boolean}
 */
var isEmpty = function (obj) {
    for (const _ in obj) return false;
    return true;
}