# Useful Web APIs for Real-Time Collaborative Text Editor

This document lists the most important browser APIs for building a collaborative text editor, based on the PRD requirements.

## 1. Core Editing & Formatting
- **ContentEditable**: Enables in-browser text editing.
- **Selection API**: Manage user selections and collaborative cursors.
- **Range API**: Manipulate document fragments and selections.
- **Clipboard API**: Support copy/paste operations.

## 2. Real-Time Communication
- **WebSocket API**: Real-time, bidirectional communication between clients and server.
- **Broadcast Channel API**: Communication between browser tabs (optional).

## 3. State & Storage
- **Web Storage API** (`localStorage`, `sessionStorage`): Local backup and recovery.
- **IndexedDB API**: Robust client-side storage, offline support.

## 4. User Presence & UI
- **Notification API**: Join/leave and collaboration notifications.
- **Pointer Events**: Track cursor positions and colored cursors.

## 5. Document Management
- **File API**: Import/export documents.
- **URL API**: Shareable document links.

## 6. Security & Accessibility
- **Credential Management API**: Authentication flows.
- **HTML DOM API**: General document manipulation.
- **Accessibility APIs**: WCAG compliance.

## 7. Advanced Features (Post-MVP)
- **MutationObserver**: Track document changes.
- **History API**: Version history, undo/redo.

---

These APIs cover collaborative editing, real-time updates, formatting, user presence, document management, and security as described in the PRD. Refer to MDN for details and usage examples.
