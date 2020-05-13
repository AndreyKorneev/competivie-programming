" Enable modern Vim features not compatible with Vi spec.
set nocompatible
filetype off

" set the runtime path to include Vundle and initialize
set rtp+=~/.config/nvim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
"
" == Formatters
Plugin 'google/vim-maktaba'
Plugin 'google/vim-codefmt'
" Also add Glaive, which is used to configure codefmt's maktaba flags. See
" `:help :Glaive` for usage.
Plugin 'google/vim-glaive'
Plugin 'rhysd/vim-clang-format'

Plugin 'preservim/nerdtree'
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
Plugin 'dikiaap/minimalist'
Plugin 'jlanzarotta/bufexplorer'
Plugin 'scrooloose/nerdcommenter'
Plugin 'mhinz/vim-signify'
Plugin 'mileszs/ack.vim'
Plugin 'Yggdroot/indentLine'
Plugin 'majutsushi/tagbar'
Plugin 'Valloric/YouCompleteMe', { 'do': './install.py' }
" Debugger.
Plugin 'Conque-GDB'
" Plugin 'wincent/command-t'
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call vundle#end()            " required

set encoding=utf-8
filetype plugin indent on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line


" =============== General Settings
syntax on
set hidden
set tabstop=2
set shiftwidth=2
set expandtab
set number
set shiftround    " use multiple of shiftwidth when indenting with '<' and '>'
set showmatch     " set show matching parenthesis
set ignorecase    " ignore case when searching
set smartcase     " ignore case if search pattern is all lowercase, case-sensitive otherwise
set hlsearch      " highlight search terms
set incsearch     " show search matches as you type
set title                " change the terminal's title
set visualbell           " don't beep
set noerrorbells         " don't beep
set pastetoggle=<F2>     " must have!
set mouse=a
:imap jj <Esc>

" =============== Key bindings
nnoremap ; :
let mapleader=','

" Make the keyboard faaaaaaast
set ttyfast
set timeout timeoutlen=1000 ttimeoutlen=50
nnoremap <leader>w <C-w>v<C-w>l
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

" Toggle show/hide invisible chars
nnoremap <leader>I :set list!<cr>

" =============== Color scheme
set t_Co=256
colorscheme minimalist

highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%81v.\+/
highlight ColorColumn ctermbg=gray
set colorcolumn=80
" This color scheme also built-in with airline theme. If you wanna use:
"
let g:airline_theme='minimalist'
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#enabled = 1

" =============== Autocomplete
let g:ycm_global_ycm_extra_conf="~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py"
let g:ycm_server_keep_logfiles = 1
let g:ycm_server_log_level = 'debug'

" Make the keyboard faaaaaaast
set ttyfast
set timeout timeoutlen=1000 ttimeoutlen=50
" Window switching
nnoremap <leader>w <C-w>v<C-w>l
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

nnoremap <leader>jd :YcmCompleter GoTo<CR>
nnoremap <leader>ji :YcmCompleter GoToInclude<CR>
nnoremap <leader>jt :YcmCompleter GetType<CR>
nnoremap <leader>jp :YcmCompleter GetParent<CR>

nnoremap <leader>jf :YcmCompleter FixIt<CR>
nnoremap <leader>jr :YcmCompleter RefactorRename <C-R><C-W>

nnoremap <leader>ss :s/<C-R><C-W>/<C-R><C-W>/g
nnoremap <leader>sa :%s/<C-R><C-W>/<C-R><C-W>/g

let g:ycm_min_num_of_chars_for_completion=2
let g:ycm_complete_in_comments=1
let g:ycm_seed_identifiers_with_syntax=1

" =============== Nerd Tree
"map <C-n> :NERDTreeToggle<CR>
nmap <leader>n :NERDTreeFind<CR>
nmap <leader>m :NERDTreeToggle<CR>
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 1 && isdirectory(argv()[0]) && !exists("s:std_in") | exe 'NERDTree' argv()[0] | wincmd p | ene | endif
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
let g:NERDTreeDirArrowExpandable = '>'
let g:NERDTreeDirArrowCollapsible = 'v'

" =============== Autocmds
autocmd BufWritePre * %s/\s\+$//e
set autoread

" =============== Execute
nnoremap <leader>ri :!pbpaste > input.txt && ./run.sh run <enter>
nnoremap <leader>rr :!./run.sh run <enter>
nnoremap <leader>rn :!./run.sh new <enter>
nnoremap <leader>ni :!./run.sh new && pbpaste > input.txt <enter>
nnoremap <leader>rs :!./run.sh save<space>

function! OpenAll()
  execute "args *.h"
  execute "e segtree.h"
  execute "e main.cpp"
endfunction

" debugging
let g:ConqueGdb_Leader = '\'
