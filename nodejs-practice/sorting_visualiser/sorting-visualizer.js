/**
 * SortingVisualizer - A library for visualizing sorting algorithms
 */
class SortingVisualizer {
    /**
     * Create a sorting visualizer
     * @param {string} containerId - The ID of the container element
     * @param {object} options - Configuration options
     */
    constructor(containerId, options = {}) {
        // DOM element reference
        this.container = document.getElementById(containerId);
        if (!this.container) {
            throw new Error(`Container element with ID "${containerId}" not found`);
        }

        // Default options
        this.options = {
            arraySize: options.arraySize || 50,
            minValue: options.minValue || 5,
            maxValue: options.maxValue || 100,
            animationSpeed: options.animationSpeed || 50,
            primaryColor: options.primaryColor || '#3498db',
            comparisonColor: options.comparisonColor || '#e74c3c',
            sortedColor: options.sortedColor || '#2ecc71'
        };

        // State
        this.array = [];
        this.bars = [];
        this.animationTimeouts = [];
        this.isSorting = false;

        // Initialize
        this.generateRandomArray();
    }

    /**
     * Generate a new random array
     */
    generateRandomArray() {
        // Clear any ongoing animations
        this.stopSorting();
        
        // Generate random values
        this.array = Array(this.options.arraySize).fill().map(() => 
            Math.floor(Math.random() * (this.options.maxValue - this.options.minValue + 1)) + this.options.minValue
        );
        
        // Render the bars
        this.renderBars();
        
        return this.array;
    }

    /**
     * Set new array size
     * @param {number} size - The new array size
     */
    setArraySize(size) {
        if (size < 5 || size > 200) {
            throw new Error('Array size must be between 5 and 200');
        }
        
        this.options.arraySize = size;
        this.generateRandomArray();
    }

    /**
     * Set animation speed
     * @param {number} speed - Value between 1 and 100
     */
    setAnimationSpeed(speed) {
        if (speed < 1 || speed > 100) {
            throw new Error('Speed must be between 1 and 100');
        }
        
        this.options.animationSpeed = speed;
    }

    /**
     * Render the bars in the container
     */
    renderBars() {
        // Clear container
        this.container.innerHTML = '';
        this.bars = [];
        
        // Create bars
        for (let i = 0; i < this.array.length; i++) {
            const bar = document.createElement('div');
            bar.className = 'array-bar';
            bar.style.height = `${(this.array[i] / this.options.maxValue) * 100}%`;
            bar.style.backgroundColor = this.options.primaryColor;
            
            this.container.appendChild(bar);
            this.bars.push(bar);
        }
    }

    /**
     * Stop all ongoing animations
     */
    stopSorting() {
        this.isSorting = false;
        
        // Clear all animation timeouts
        this.animationTimeouts.forEach(timeoutId => clearTimeout(timeoutId));
        this.animationTimeouts = [];
        
        // Reset bar colors
        if (this.bars.length > 0) {
            this.bars.forEach(bar => {
                bar.style.backgroundColor = this.options.primaryColor;
            });
        }
    }

    /**
     * Helper to calculate animation delay
     * @returns {number} - Delay in ms
     */
    getAnimationDelay() {
        // Invert speed so higher value means faster
        return Math.floor(1000 / this.options.animationSpeed);
    }

    /**
     * Update bar colors
     * @param {number} index - The bar index
     * @param {string} color - The new color
     */
    updateBarColor(index, color) {
        if (index >= 0 && index < this.bars.length) {
            this.bars[index].style.backgroundColor = color;
        }
    }

    /**
     * Update bar height
     * @param {number} index - The bar index
     * @param {number} value - The new value
     */
    updateBarHeight(index, value) {
        if (index >= 0 && index < this.bars.length) {
            this.array[index] = value;
            this.bars[index].style.height = `${(value / this.options.maxValue) * 100}%`;
        }
    }

    /**
     * Swap two bars
     * @param {number} i - First index
     * @param {number} j - Second index
     */
    swap(i, j) {
        // Swap array values
        [this.array[i], this.array[j]] = [this.array[j], this.array[i]];
        
        // Swap bar heights
        const heightI = this.bars[i].style.height;
        this.bars[i].style.height = this.bars[j].style.height;
        this.bars[j].style.height = heightI;
    }

    /**
     * Create an animation step
     * @param {function} callback - Function to execute
     * @param {number} delay - Animation delay in ms
     */
    addAnimationStep(callback, delay = 0) {
        if (!this.isSorting) return;
        
        const timeoutId = setTimeout(() => {
            if (this.isSorting) {
                callback();
            }
        }, delay);
        
        this.animationTimeouts.push(timeoutId);
    }

    /**
     * Mark array as sorted
     */
    markSorted() {
        if (!this.isSorting) return;
        
        const markBar = (index, delay) => {
            this.addAnimationStep(() => {
                this.updateBarColor(index, this.options.sortedColor);
                
                if (index === this.array.length - 1) {
                    this.isSorting = false;
                }
            }, delay);
        };
        
        for (let i = 0; i < this.array.length; i++) {
            markBar(i, i * 10);
        }
    }

    /**
     * Run bubble sort
     */
    bubbleSort() {
        this.stopSorting();
        this.isSorting = true;
        
        const animations = [];
        const arrayCopy = [...this.array];
        
        // Generate animations
        for (let i = 0; i < arrayCopy.length - 1; i++) {
            for (let j = 0; j < arrayCopy.length - i - 1; j++) {
                // Compare adjacent elements
                animations.push({type: 'compare', indices: [j, j+1]});
                
                if (arrayCopy[j] > arrayCopy[j + 1]) {
                    // Swap elements
                    [arrayCopy[j], arrayCopy[j + 1]] = [arrayCopy[j + 1], arrayCopy[j]];
                    animations.push({type: 'swap', indices: [j, j+1]});
                }
                
                // Revert color
                animations.push({type: 'revert', indices: [j, j+1]});
            }
            
            // Mark element as sorted
            animations.push({type: 'sorted', index: arrayCopy.length - 1 - i});
        }
        
        // Mark first element as sorted (last one remaining)
        animations.push({type: 'sorted', index: 0});
        
        // Execute animations
        let delay = 0;
        const animationDelay = this.getAnimationDelay();
        
        animations.forEach((animation, index) => {
            this.addAnimationStep(() => {
                switch (animation.type) {
                    case 'compare':
                        this.updateBarColor(animation.indices[0], this.options.comparisonColor);
                        this.updateBarColor(animation.indices[1], this.options.comparisonColor);
                        break;
                    case 'swap':
                        this.swap(animation.indices[0], animation.indices[1]);
                        break;
                    case 'revert':
                        this.updateBarColor(animation.indices[0], this.options.primaryColor);
                        this.updateBarColor(animation.indices[1], this.options.primaryColor);
                        break;
                    case 'sorted':
                        this.updateBarColor(animation.index, this.options.sortedColor);
                        break;
                }
                
                // Check if sorting is complete
                if (index === animations.length - 1) {
                    this.isSorting = false;
                }
            }, delay);
            
            delay += animationDelay;
        });
    }
    
    /**
     * Run selection sort
     */
    selectionSort() {
        this.stopSorting();
        this.isSorting = true;
        
        const animations = [];
        const arrayCopy = [...this.array];
        
        // Generate animations
        for (let i = 0; i < arrayCopy.length - 1; i++) {
            let minIdx = i;
            
            // Find minimum element
            for (let j = i + 1; j < arrayCopy.length; j++) {
                animations.push({type: 'compare', indices: [minIdx, j]});
                
                if (arrayCopy[j] < arrayCopy[minIdx]) {
                    animations.push({type: 'revert', index: minIdx});
                    minIdx = j;
                    animations.push({type: 'min', index: minIdx});
                } else {
                    animations.push({type: 'revert', index: j});
                }
            }
            
            // Swap minimum element with first element
            if (minIdx !== i) {
                [arrayCopy[i], arrayCopy[minIdx]] = [arrayCopy[minIdx], arrayCopy[i]];
                animations.push({type: 'swap', indices: [i, minIdx]});
            }
            
            animations.push({type: 'sorted', index: i});
        }
        
        // Mark last element as sorted
        animations.push({type: 'sorted', index: arrayCopy.length - 1});
        
        // Execute animations
        let delay = 0;
        const animationDelay = this.getAnimationDelay();
        
        animations.forEach((animation, index) => {
            this.addAnimationStep(() => {
                switch (animation.type) {
                    case 'compare':
                        this.updateBarColor(animation.indices[0], this.options.comparisonColor);
                        this.updateBarColor(animation.indices[1], this.options.comparisonColor);
                        break;
                    case 'min':
                        this.updateBarColor(animation.index, '#ff9800'); // Orange for min element
                        break;
                    case 'swap':
                        this.swap(animation.indices[0], animation.indices[1]);
                        break;
                    case 'revert':
                        if (Array.isArray(animation.indices)) {
                            animation.indices.forEach(idx => {
                                this.updateBarColor(idx, this.options.primaryColor);
                            });
                        } else {
                            this.updateBarColor(animation.index, this.options.primaryColor);
                        }
                        break;
                    case 'sorted':
                        this.updateBarColor(animation.index, this.options.sortedColor);
                        break;
                }
                
                // Check if sorting is complete
                if (index === animations.length - 1) {
                    this.isSorting = false;
                }
            }, delay);
            
            delay += animationDelay;
        });
    }
}
