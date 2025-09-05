document.addEventListener('DOMContentLoaded', () => {
    const editor = document.getElementById('editor');
    const info = document.createElement('div');
    info.id = 'selection-info';
    info.style.marginTop = '1em';
    info.style.background = '#f0f0f0';
    info.style.padding = '0.5em';
    info.style.fontSize = '0.9em';
    editor.parentNode.insertBefore(info, editor.nextSibling);

    function updateSelectionInfo() {
        const selection = window.getSelection();
        if (!selection || selection.rangeCount === 0) {
            info.textContent = 'No selection.';
            return;
        }
        const range = selection.getRangeAt(0);
        info.innerHTML = `
      <b>Selection Info:</b><br>
      Anchor Offset: ${selection.anchorOffset}<br>
      Focus Offset: ${selection.focusOffset}<br>
      Is Collapsed: ${selection.isCollapsed}<br>
      Selected Text: "${selection.toString()}"
    `;
    }

    editor.addEventListener('mouseup', updateSelectionInfo);
    editor.addEventListener('keyup', updateSelectionInfo);
    editor.addEventListener('focus', updateSelectionInfo);
    editor.addEventListener('blur', updateSelectionInfo);
});
