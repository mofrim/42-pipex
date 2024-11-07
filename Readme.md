# 42's pipex

## Takeaways

- The child process gets a copy of the open file descriptors from the parent.
  Closing such an parent-fd inside the child does not close it for the parent!

## Ressources

- [https://www.rozmichelle.com/pipes-forks-dups/](https://www.rozmichelle.com/pipes-forks-dups/)
- 
