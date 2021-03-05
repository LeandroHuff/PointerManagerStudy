.PHONY: clean All

All:
	@echo "----------Building project:[ PointerManagerStudy - Debug ]----------"
	@"$(MAKE)" -f  "PointerManagerStudy.mk"
clean:
	@echo "----------Cleaning project:[ PointerManagerStudy - Debug ]----------"
	@"$(MAKE)" -f  "PointerManagerStudy.mk" clean
