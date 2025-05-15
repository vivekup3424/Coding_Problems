import { writable } from 'svelte/store';

type AlertType = 'success' | 'error' | 'info' | 'warning';

interface AlertState {
    message: string;
    type: AlertType;
    duration: number;
    visible: boolean;
}

function createAlertStore() {
    const { subscribe, set, update } = writable<AlertState>({
        message: '',
        type: 'info',
        duration: 2000,
        visible: false
    });

    return {
        subscribe,
        show: (message: string, type: AlertType = 'info', duration: number = 2000) => {
            set({ message, type, duration, visible: true });
        },
        hide: () => {
            update(state => ({ ...state, visible: false }));
        }
    };
}

export const alertStore = createAlertStore();