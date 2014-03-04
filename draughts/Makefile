################################################################################
#                                                                              #
#                       Makefile in 3_langage de modules                       #
#                       For Epitech's λ Knowledge Unit                         #
#                       Made by: David GIRON                                   #
#                                                                              #
################################################################################

ARCH = WIN

NAME = a.out

ML= main.ml

MLI = 

CMI = $(MLI:.mli=.cmi)
CMO = $(ML:.ml=.cmo)
CMX = $(ML:.ml=.cmx)

OCAMLDPE = ocamldep
CAMLFLAGS = -w Aelz -warn-error A
OCAMLC = ocamlc $(CAMLFLAGS)
OCAMLOPT = ocamlopt $(CAMLFLAGS)
OCAMLDOC = ocamldoc -html -d $(ROOT)/doc

## utils
ifeq ($(ARCH), WIN)
	RM = del /F
else
	RM = rm -f
endif

byte: .depend $(CMI) $(NAME).byte

all: .depend $(CMI) $(NAME)

$(NAME): $(CMX)
	@$(OCAMLOPT) -o $@ $(CMX)
	@echo "[OK] $(NAME) linked"

$(NAME).byte: $(CMO)
	@$(OCAMLC) -o $@ $(CMO)
	@echo "[OK] $(NAME).byte linked"

%.cmx: %.ml
	@$(OCAMLOPT) -c $<
	@echo "[OK] [$<] builded"

%.cmo: %.ml
	@$(OCAMLC) -c $<
	@echo "[OK] [$<] builded"

%.cmi: %.mli
	@$(OCAMLC) -c $<
	@echo "[OK] [$<] builded"

documentation: $(CMI)
	@$(OCAMLDOC) $(MLI)
	@echo "[OK] Documentation"

re: fclean all

clean:
	@$(RM) *.cm* *.o .depend *~
	@echo "[OK] clean"

fclean: clean
	@$(RM) $(NAME) $(NAME).byte
	@echo "[OK] fclean"

.depend:
	@$(RM) .depend
	@$(OCAMLDPE) $(MLI) $(ML) > .depend
	@echo "[OK] dependencies"

################################################################################
