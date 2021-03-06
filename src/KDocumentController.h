#import <Cocoa/Cocoa.h>

@class KTabContents, KCloseCycleContext, KBrowserWindowController, KURLHandler;

@interface KDocumentController : NSDocumentController {
  KCloseCycleContext *closeCycleContext_;
  NSMutableDictionary *urlHandlers_;

  // atomically monotonically incrementing counter
  int32_t untitledNumberCounter_;
}

@property(readonly) int32_t nextUntitledNumber;

// Typed sharedDocumentController
+ (KDocumentController*)kodController;

// Returns a set (unique) of all windows used by |documents|
- (NSSet*)windows;

- (void)addTabContents:(KTabContents*)tab
  withWindowController:(KBrowserWindowController*)windowController
          inForeground:(BOOL)foreground
     groupWithSiblings:(BOOL)groupWithSiblings;

- (KURLHandler*)urlHandlerForURL:(NSURL*)url;

// --------------------------------------------------------------------
// high-level operners which will dispatch opening to the background

// Open |urls| concurrently in the background, inserting tabs by closest sibling
// edit distance (groupWithSiblings:YES). Only the last tab opened will be
// brought to foreground and become first responder.
- (void)openDocumentsWithContentsOfURLs:(NSArray*)urls
                   withWindowController:(KBrowserWindowController*)windowController
                               priority:(long)priority
         nonExistingFilesAsNewDocuments:(BOOL)newDocForNewURLs
                               callback:(dispatch_block_t)callback;

// Open |urls| in frontmost window with high priority
- (void)openDocumentsWithContentsOfURLs:(NSArray*)urls
         nonExistingFilesAsNewDocuments:(BOOL)newDocForNewURLs
                               callback:(dispatch_block_t)callback;

// Open |urls| in frontmost window with high priority
- (void)openDocumentsWithContentsOfURLs:(NSArray*)urls
                               callback:(dispatch_block_t)callback;

// Open |url| in frontmost window with high priority
- (void)openDocumentsWithContentsOfURL:(NSURL*)url
                              callback:(dispatch_block_t)callback;

// --------------------------------------------------------------------
// lower level openers which run in the current thread

- (id)openDocumentWithContentsOfURL:(NSURL *)absoluteURL
               withWindowController:(KBrowserWindowController*)windowController
                  groupWithSiblings:(BOOL)groupWithSiblings
                            display:(BOOL)displayDocument
                              error:(NSError **)outError;

- (void)finalizeOpenDocument:(KTabContents*)tab
        withWindowController:(KBrowserWindowController*)windowController
           groupWithSiblings:(BOOL)groupWithSiblings
                     display:(BOOL)display;

@end
