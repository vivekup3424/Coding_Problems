// Initialize the sorting visualizer
const visualizer = new SortingVisualizer('array-container', {
    arraySize: 50,
    minValue: 5,
    maxValue: 100,
    animationSpeed: 50
});

// DOM Elements
const arraySizeInput = document.getElementById('array-size');
const arraySizeValue = document.getElementById('size-value');
const sortingSpeedInput = document.getElementById('sorting-speed');
const sortingSpeedValue = document.getElementById('speed-value');
const generateArrayBtn = document.getElementById('generate-array');
const bubbleSortBtn = document.getElementById('bubble-sort');
const stopSortBtn = document.getElementById('stop-sort');

// Event Listeners
arraySizeInput.addEventListener('input', function() {
    const size = parseInt(this.value);
    arraySizeValue.textContent = size;
    visualizer.setArraySize(size);
});

sortingSpeedInput.addEventListener('input', function() {
    const speed = parseInt(this.value);
    sortingSpeedValue.textContent = speed;
    visualizer.setAnimationSpeed(speed);
});

generateArrayBtn.addEventListener('click', function() {
    visualizer.generateRandomArray();
});

bubbleSortBtn.addEventListener('click', function() {
    // Disable controls during sorting
    setControlsState(true);
    
    // Start bubble sort
    visualizer.bubbleSort();
    
    // Check when sorting is complete to re-enable controls
    const checkSortingStatus = setInterval(() => {
        if (!visualizer.isSorting) {
            setControlsState(false);
            clearInterval(checkSortingStatus);
        }
    }, 100);
});

stopSortBtn.addEventListener('click', function() {
    visualizer.stopSorting();
    setControlsState(false);
});

// Helper function to enable/disable controls during sorting
function setControlsState(disabled) {
    arraySizeInput.disabled = disabled;
    sortingSpeedInput.disabled = disabled;
    generateArrayBtn.disabled = disabled;
    bubbleSortBtn.disabled = disabled;
}
