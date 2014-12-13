(global-linum-mode)
(custom-set-variables
'(prelude-whitespace nil)
'(tab-width 4)
)
(yas-global-mode)
(key-chord-define-global "OO" 'prelude-smart-open-line-above)
(defun my:c-common-hook()
  ;;(local-set-key (kbd "M-O") 'helm-projectile-find-other-file)
  (local-set-key (kbd "RET") 'prelude-smart-open-line)
  (setq c-basic-offset 4)
)
(add-hook 'c-mode-common-hook 'my:c-common-hook)
