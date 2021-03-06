"""""" Basic Edit Setting """"""
set nu
set tabstop=4
set shiftwidth=4
set expandtab
set magic
set ignorecase
set nocompatible 
set nobackup
set incsearch
set mouse=a
set backspace=2

set guioptions-=m
set guioptions-=r

""" file encoding """
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,gb2312

"""plugin  setting  """"
syntax  on
filetype plugin  on
filetype plugin indent on

""""" colorschem """""""
set t_Co=256
"colorscheme seoul256
colorschem apprentice
set background=dark
		 
""""Set mapleade """"r
let mapleader = ","
call plug#begin() 

"plugins
Plug 'bling/vim-airline'
Plug 'godlygeek/csapprox'
Plug 'majutsushi/tagbar'
Plug 'scrooloose/nerdtree'
Plug 'terryma/vim-multiple-cursors'
Plug 'vim-scripts/vimwiki' 
Plug 'tomtom/tcomment_vim'
Plug 'Valloric/YouCompleteMe' 
Plug 'yonchu/accelerated-smooth-scroll'
Plug 'romainl/Apprentice'
Plug 'kien/ctrlp.vim'
Plug 'tpope/vim-fugitive' 
Plug 'junegunn/seoul256.vim'
Plug 'jlanzarotta/bufexplorer'
Plug 'vim-scripts/a.vim'
Plug 'rust-lang/rust.vim'
Plug 'phildawes/racer'
call plug#end()            " required

"""""" Racer  Setting   """""
let g:racer_cmd = "/home/bruce/.vim/plugged/racer/target/release/racer"
let $RUST_SRC_PATH = "/usr/local/src/rust/src"

"""""""""vimwiki """"""""""
let g:vimwiki_list = [{'path': '/home/bruce/.Wiki/', 
  \ 'template_path': '/home/bruce/.Wiki/', 
  \ 'template_default': 'default', 
  \ 'template_ext': '.tpl',
  \ 'path_html': '/home/bruce/.Wiki_html'}]


""""""""key mapping""""""""""""""

"Fast Reloading of the .vimrc
map <leader>ss :e ~/.vimrc <cr>
"Fast split the window
noremap <leader>sp :split<cr>
noremap <leader>v :vsp<CR>
noremap <leader>a :A<CR>
noremap <leader>as :AS<CR>
nnoremap W :w<cr>
nnoremap Q :q<cr>
inoremap jj <ESC>
"""

"""""" <ESC> mapping """"""""""

" tab switch 
noremap <C-H> :tabp<CR>
noremap <C-L> :tabn<CR>
noremap <C-J> :tabc<CR>
noremap <C-K> :tabe<CR> 


""""" Fast Indeting """"""""""
vnoremap < <gv 
vnoremap > >gv

""""  Fast convert to html """"""
map va :VimwikiAll2HTML<cr>

""""" tagbar configure """""""
map tl :TagbarToggle<cr>
let g:tagbar_width = 15

" Ctrlp mapping
nnoremap <leader>cp :CtrlP<cr>
nnoremap <leader>mp :CtrlPMRUFiles<CR>
nnoremap <leader>wp :CtrlPCurWD<CR>
nnoremap <leader>bp :CtrlPBuffer<CR>


"""""""""""nerdtree """"""""""
let NERDTreeWinSize=20 
map ne :NERDTreeToggle<CR> 

""""""""""""""""""""youcompleteme """"""""""""""""""""''"
set completeopt-=preview
let g:ycm_confirm_extra_conf = 0
let g:ycm_global_ycm_extra_conf = '~/.vim/plugged/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py' 
let g:ycm_collect_identifiers_from_tags_files=1
let g:ycm_register_as_syntastic_checker = 0
let g:ycm_min_num_of_chars_for_completion= 1
let g:ycm_complete_in_comments = 1 
let g:ycm_seed_identifiers_with_syntax=1	" 语法关键字补全
let g:ycm_auto_trigger = 1
let g:ycm_key_invoke_completion = '<C-a>'

"""""""""""""synastics setting """""""""""""""""""""""""''
" let g:syntastic_error_symbol = 'x'  
" let g:syntastic_warning_symbol = '!'  
" let g:syntastic_check_on_open = 1
" let g:syntastic_cpp_include_dirs = ['/usr/include/']
" let g:syntastic_cpp_remove_include_errors = 1 
" let g:syntastic_cpp_check_header = 1 
" let g:syntastic_cpp_compiler = 'clang++' 
" let g:syntastic_cpp_compiler_options = '-std=c++11 -stdlib=libstdc++'

" 禁止缓存匹配项，每次都重新生成匹配项
let g:ycm_cache_omnifunc=0
nnoremap <leader>jd :YcmCompleter GoToDefinitionElseDeclaration <CR> 
nnoremap <leader>yd :YcmDiags<CR> 
"complete in the strings of input
let g:ycm_complete_in_strings = 1 
"complete the syntax keyword
let g:ycm_collect_identifiers_from_comments_and_strings = 1


"""vim-fugitive setting """""""'
nnoremap <silent> <leader>gs :Gstatus<CR>
nnoremap <silent> <leader>gd :Gdiff<CR>
nnoremap <silent> <leader>gc :Gcommit<CR>
nnoremap <silent> <leader>gb :Gblame<CR>
nnoremap <silent> <leader>gl :Glog<CR>
nnoremap <silent> <leader>gp :Git push<CR>
nnoremap <silent> <leader>gw :Gwrite<CR>
nnoremap <silent> <leader>gr :Gremove<CR>


