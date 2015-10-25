@echo off

set pwd=%cd%
del "%pwd%\SDCard\*.Anita*
rd /Q /s "%pwd%\SDCard\sd_card_fat16.cydsn\Generated_Source"
rd /Q /s "%pwd%\SDCard\sd_card_fat16.cydsn\codegentemp"
rd /Q /s "%pwd%\SDCard\sd_card_fat16.cydsn\CortexM0"
rd /Q /s "%pwd%\SDCard\sd_card_fat16.cydsn\Export"
del "%pwd%\SDCard\sd_card_fat16.cydsn\*.cycdx"
del "%pwd%\SDCard\sd_card_fat16.cydsn\*.cyfit"
del "%pwd%\SDCard\sd_card_fat16.cydsn\*.Anita Mehta"
del "%pwd%\SDCard\sd_card_fat16.cydsn\*.rpt"
del "%pwd%\SDCard\sd_card_fat16.cydsn\*.html"

rd /Q /s "%pwd%\SDCard\sd_card_fat32.cydsn\Generated_Source"
rd /Q /s "%pwd%\SDCard\sd_card_fat32.cydsn\codegentemp"
rd /Q /s "%pwd%\SDCard\sd_card_fat32.cydsn\CortexM0"
rd /Q /s "%pwd%\SDCard\sd_card_fat32.cydsn\Export"
del "%pwd%\SDCard\sd_card_fat32.cydsn\*.cycdx"
del "%pwd%\SDCard\sd_card_fat32.cydsn\*.cyfit"
del "%pwd%\SDCard\sd_card_fat32.cydsn\*.Anita Mehta"
del "%pwd%\SDCard\sd_card_fat32.cydsn\*.rpt"
del "%pwd%\SDCard\sd_card_fat32.cydsn\*.html"

