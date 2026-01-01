Date.prototype.nextDay = function(){
    const date = new Date(this.valueOf());
    date.setDate(date.getDate() + 1);
    return date.toISOString().split('T')[0];
}

const date = new Date('2024-06-15');
const nextDate = date.nextDay();
console.log(nextDate)