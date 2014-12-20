(global-linum-mode)
(require 'pulse)
;;(pulse-enable-integration-advice)
(setq pulse-command-advice-flag t)
(defadvice goto-line (after pulse-advice activate)
  "Cause the line that is `goto'd to pulse when the cursor gets there."
  (recenter-top-bottom)
  (pulse-momentary-highlight-one-line (point))
  )

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(company-idle-delay 0.1)
 '(prelude-whitespace nil)
 '(pulse-delay 0.08)
 '(tab-width 4))
(yas-global-mode)
(key-chord-define-global "OO" 'prelude-smart-open-line-above)

(defun my:c-common-hook()
  ;;(local-set-key (kbd "M-O") 'helm-projectile-find-other-file)
 ;; (local-set-key (kbd "RET") 'prelude-smart-open-line)
5  (c-set-style "linux")
  ;;(setq electric-indent-mode t)
  (electric-indent-mode t)
  (setq c-basic-offset 4)
  (c-toggle-hungry-state t)
  (c-toggle-auto-newline)
  (add-to-list 'c-hanging-semi&comma-criteria 'c-semi&comma-no-newlines-before-nonblanks)
  ;;(define-key c-mode-base-map ";" nil)
  (add-to-list 'company-backends 'company-c-headers)
  )
(defun my:c++-hook()
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))
  )
(add-hook 'c-mode-common-hook 'my:c-common-hook)
(add-hook 'c++-mode-hook 'my:c++-hook)
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
