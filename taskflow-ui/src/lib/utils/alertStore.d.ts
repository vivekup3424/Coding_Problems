type AlertType = 'success' | 'error' | 'info' | 'warning';
interface AlertState {
    message: string;
    type: AlertType;
    duration: number;
    visible: boolean;
}
export declare const alertStore: {
    subscribe: (this: void, run: import("svelte/store").Subscriber<AlertState>, invalidate?: () => void) => import("svelte/store").Unsubscriber;
    show: (message: string, type?: AlertType, duration?: number) => void;
    hide: () => void;
};
export {};
