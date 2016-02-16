
/*{{BLOCK(background)                                                   */

/*======================================================================*/
/*                                                                      */
/* background, 80x56@8,                                                 */
/* Transperent palette entry: 0.                                        */
/* + palette 256 entries, not compressed                                */
/* + 60 tiles (t|f|p reduced) not compressed                            */
/* + regular map (flat), not compressed, 10x7                           */
/* Total size: 512 + 3840 + 140 = 4492                                  */
/*                                                                      */
/* Time-stamp: 2009-06-28, 00:33:59                                     */
/* Exported by Cearn's GBA Image Transmogrifier                         */
/* ( http://www.coranac.com )                                           */
/*                                                                      */
/*======================================================================*/

#ifndef __BACKGROUND__
#define __BACKGROUND__

#define backgroundPalLen 512
extern const unsigned short backgroundPal[256];

#define backgroundTilesLen 3840
extern const unsigned short backgroundTiles[1920];

#define backgroundMapLen 140
extern const unsigned short backgroundMap[70];

#endif /* __BACKGROUND__                                                */

/*}}BLOCK(background)                                                   */
